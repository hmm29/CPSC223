#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

static int TASK_COUNT = 0;
static int FLAG_COUNT = 0;

/*
 * Function: getTasks
 * ------------------
 * Generates array of tasks with task runtime arguments passed to program
 *
 * argc: number of command-line arguments
 * argv: array of command-line arguments
 *
 * returns: an integer array of the task runtimes in order
 */

int *getTasks(int argc, char **argv) {
    int i = 0; /* argv index pointer */
    int j = 0; /* tasks index pointer */
    int counter = 0; /* task counter */

    /* start with index 2, because argv[0] has "Psched" and argv[1] has number of processors */
    for (i = 2; i < argc; i++) {
        if (isdigit(argv[i][0])) {
            counter++;
        } else {
            break;
        }
    }
   int *tasks = malloc(counter * sizeof(int));

    if(counter > 0) {
        TASK_COUNT = counter;
    }

    // copy runtime values into tasks array
    for (i = 2; i < argc && j < counter; i++) {
        tasks[j] = atoi(argv[i]);
        j++;
    }
   
    return tasks;
}

/*
 * Function: getTaskCount
 * ------------------------
 * Gets number of tasks typed in
 *
 * returns: number of tasks
 */
int getTaskCount() {
    return TASK_COUNT;
}

/*
 * Function: getFlags
 * ------------------
 * Generates array of flags with flag arguments passed to program
 *
 * argc: number of command-line arguments
 * argv: array of command-line arguments
 *
 * returns: an array of flag strings
 */

char **getFlags(int argc, char **argv) {
    int i = 0; /* argv index pointer */
    int j = 0; /* flags index pointer */
    int counter = 0; /* flag counter */

    for (i = 3; i < argc; i++) { /* start with index 2, because argv[0] has "Psched" and argv[1] has number of processors */
        if (isdigit(argv[i][0])) { /* if digit then skip */
            continue;
        } else {
            counter++;
        }
    }

    char **flags = malloc(counter * sizeof(char*));
    FLAG_COUNT = counter;

    // copy flags into flags array
    for (i = 3; i < argc && j < counter; i++) {
        if (isdigit(argv[i][0])) {
            continue;
         } else {
            flags[j] = argv[i];
            j++;
        }
     }

    return flags;
}

/*
 * Function: getFlagCount
 * ------------------------
 * Gets number of flags typed in
 *
 * returns: number of flags
 */
int getFlagCount() {
    return FLAG_COUNT;
}

/*
 * Function: getMaxWorkload
 * ------------------------
 * Gets minimized maximum workload using assignment specified by flag argument
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * flag: assignment method specification
 *
 * returns: value of maximum workload using assignment method
 */

int getMaxWorkLoad(int *processors, int nProc, int *tasks, char *flag) {
    if (strcmp(flag, "-opt") == 0) {
        return backtrackToOpt(processors, nProc, tasks, TASK_COUNT, 0);
    }

    if (strcmp(flag, "-lw") == 0) {
        return leastWorkload(processors, nProc, tasks);
    }

    if (strcmp(flag, "-lwd") == 0) {
        return leastWorkloadDecreasing(processors, nProc, tasks);
    }

    if (strcmp(flag, "-bw") == 0) {
        return bestWorkload(processors, nProc, tasks);
    }

    if (strcmp(flag, "-bwd") == 0) {
        return bestWorkloadDecreasing(processors, nProc, tasks);
    }

   return -1;
}


/*
 * Function: backtrackToOpt
 * ------------------------
 * Uses backtracking to find an assignment that minimizes maximum workload among processors
 *
 * processors: array of processors
 * tasks: array of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int backtrackToOpt(int *processors, int nProc, int *tasks, int taskCount, int minMaxWorkload) {	
	int idx = getMaxWorkloadProcessorIndex(processors,nProc);

	if(processors[idx] < minMaxWorkload || minMaxWorkload == 0) {
		minMaxWorkload = processors[idx];
	}
	
	if(taskCount <= 0) {
	   return minMaxWorkload;
	}

	int i;
	for(i = 0; i <= taskCount; i++) {
	  processors[nProc] = tasks[i];
	
	taskCount -= 1;
	nProc -= 1;

	minMaxWorkload = backtrackToOpt(processors, nProc, tasks, taskCount, minMaxWorkload);
	}
	return minMaxWorkload;
}

/*
 * Function: leastWorkload
 * -----------------------
 * assigns tasks in order they appear, greedily choosing processor with least workload
 *
 * processors: array of processors
 * tasks: array of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int leastWorkload(int *processors, int nProc, int *tasks) {
    int i; /* index counter */
    int idx; /* index of least workload processor */
  
    for(i = 0; i < TASK_COUNT; i++) {
        idx = getLeastWorkloadProcessorIndex(processors, nProc);
        processors[idx] += tasks[i]; /* assign the task to the least workload processor */
    }

    idx = getMaxWorkloadProcessorIndex(processors, nProc);
    return processors[idx];
}

/*
 * Function: leastWorkloadDecreasing
 * ---------------------------------
 * assigns tasks in decreasing order, then uses least workload heuristic
 *
 * processors: array of processors
 * tasks: array of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int leastWorkloadDecreasing(int *processors, int nProc, int *tasks) {
    int *sortedTasksDecreasing = quicksort(tasks);
    return leastWorkload(processors, nProc, sortedTasksDecreasing);
}

/*
 * Function: bestWorkload
 * ----------------------
 * assign tasks in order they appear, greedily choosing busiest processor for which the assignment
 * would not increase the maximum workload
 *
 * processors: array of processors
 * tasks: array of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int bestWorkload(int *processors, int nProc, int *tasks) {
    int i; /* index counter */
    int idx; /* index of least workload processor */
    int currentMaxWorkload = 0;

    for(i = 0; i < TASK_COUNT; i++) {
        idx = getLeastWorkloadProcessorIndex(processors, nProc);

        if(processors[idx] + tasks[i] >= currentMaxWorkload) {
            currentMaxWorkload = processors[idx] + tasks[i];
	    processors[idx] += tasks[i];
        }
	else {
	    int j;
	    int busiestProcessorWorkloadThatMinimizesMaximum = processors[0];
            for(j = 0; j < nProc; j++) {
		if((processors[j] + tasks[i] <= currentMaxWorkload) && (busiestProcessorWorkloadThatMinimizesMaximum <= processors[j])) {
			busiestProcessorWorkloadThatMinimizesMaximum = processors[j];
			idx = j;
		} 
	    }
	    processors[idx] += tasks[i];
        }
    }

    idx = getMaxWorkloadProcessorIndex(processors, nProc);
    return processors[idx];
}

/*
 * Function: bestWorkloadDecreasing
 * --------------------------------
 * assigns tasks in decreasing order, then uses best workload heuristic
 *
 * processors: array of processors
 * tasks: array of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int bestWorkloadDecreasing(int *processors, int nProc, int *tasks) {
    int *sortedTasksDecreasing = quicksort(tasks);
    return bestWorkload(processors, nProc, sortedTasksDecreasing);
}

/*
 * Function: comparatorFn
 * ---------------------
 * compares values to be in descending order
 *
 * a: pointer to first val for comparison
 * b: pointer to second val for comparison
 *
 * returns: the sorted input array, with elements in order specified by order argument
 */

int comparatorFn (const void *a, const void *b)
{
    return *(int*)b-*(int*)a;
}

/*
 * Function: quicksort
 * -------------------
 * divide-and-conquer sort that runs in O(nlogn) amortized time, O(n^2) worst case
 *
 * array: array of ints to be sorted
 * order: ascending or descending order in returned sorted array
 *
 * returns: the sorted input array, with elements in order specified by order argument
 */

int* quicksort(int *tasks) {
    qsort(tasks, TASK_COUNT, sizeof(int), comparatorFn);
    return tasks;
}

/*
 * Function: getLeastWorkloadProcessorIndex
 * ----------------------------------------
 * get index of processor with lowest workload
 *
 * processors: array of processors, whos workloads are int values
 *
 * returns: the index of the processor with the least workload
 */

int getLeastWorkloadProcessorIndex(int *processors, int nProc) {
    int i;
    int idx = 0;
    int minimum = processors[0];

    for (i = 1 ; i < nProc; i++)
    {
        if ( processors[i] < minimum )
        {
            minimum = processors[i];
            idx = i;
        }
    }
    return idx;
}

int getMaxWorkloadProcessorIndex(int *processors, int nProc) {
 	int i;
	int idx = 0;
	int maximum = processors[0];

	for(i = 1; i < nProc; i++) {
	  if(processors[i] > maximum){
	      maximum = processors[i];
	      idx = i;
	  }
  	}
 
	return idx;
}

