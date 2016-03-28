#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

/*
 * Function: getTaskCount
 * ------------------
 * Counts number of task args
 *
 * argc: number of command-line arguments
 * argv: array of command-line arguments
 *
 * returns: task count
 */

int getTaskCount(int argc, char **argv) {
    int taskCount = 0; /* task count */

    // count number of integers after first 2 args
    for (int i = 2; i < argc; i++) {
        if (isdigit(argv[i][0])) {
            taskCount++;
        } else {
            break;
        }
    }
   
    return taskCount;
}

/*
 * Function: getFlagCount
 * ------------------
 * Counts number of flag args
 *
 * argc: number of command-line arguments
 * argv: array of command-line arguments
 * taskCount: number of task arguments to determine start idx for count
 *
 * returns: flag count
 */

int getFlagCount(int argc, char **argv, int taskCount) {
    int flagCount = 0;

    //start with first arg after tasks at idx 2 + taskCount
    for (int i = 2 + taskCount; i < argc; i++) {
        // skip if is digit
        if (isdigit(argv[i][0])) {
            continue;
        } else {
            flagCount++;
        }
    }

    return flagCount;
}

/*
 * Function: getMaxWorkload
 * ------------------------
 * Gets minimized maximum workload using assignment specified by flag argument
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 * flag: assignment method specification
 *
 * returns: value of maximum workload using assignment method
 */

int getMaxWorkLoad(int *processors, int nProc, int *tasks, int taskCount, char *flag) {
    if (strcmp(flag, "-opt") == 0) {
        return backtrackToOpt(processors, nProc, tasks, taskCount);
    }

    if (strcmp(flag, "-lw") == 0) {
        return leastWorkload(processors, nProc, tasks, taskCount);
    }

    if (strcmp(flag, "-lwd") == 0) {
        return leastWorkloadDecreasing(processors, nProc, tasks, taskCount);
    }

    if (strcmp(flag, "-bw") == 0) {
        return bestWorkload(processors, nProc, tasks, taskCount);
    }

    if (strcmp(flag, "-bwd") == 0) {
        return bestWorkloadDecreasing(processors, nProc, tasks, taskCount);
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
 * taskCount: number of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int backtrackToOpt(int *processors, int nProc, int *tasks, int taskCount) {	
	return 1;
}

/*
 * Function: leastWorkload
 * -----------------------
 * assigns tasks in order they appear, greedily choosing processor with least workload
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int leastWorkload(int *processors, int nProc, int *tasks, int taskCount) {
    int idx = 0; /* index of least workload processor */
  
    for(int i = 0; i < taskCount; i++) {
        idx = getLeastWorkloadProcessorIndex(processors, nProc); // get index of least workload processor
        processors[idx] += tasks[i]; /* assign the task to the least workload processor */
    }

    idx = getMaxWorkloadProcessorIndex(processors, nProc);
    // printf("at index %d the val is %d hahah\n", idx, processors[idx]);
    return processors[idx];
}

/*
 * Function: leastWorkloadDecreasing
 * ---------------------------------
 * assigns tasks in decreasing order, then uses least workload heuristic
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */

int leastWorkloadDecreasing(int *processors, int nProc, int *tasks, int taskCount) {
    int *sortedTasksDecreasing = quicksort(tasks, taskCount);
    return leastWorkload(processors, nProc, sortedTasksDecreasing, taskCount);
}

/*
 * Function: bestWorkload
 * ----------------------
 * assign tasks in order they appear, greedily choosing busiest processor for which the assignment
 * would not increase the maximum workload
 *
 * processors: array of processors
 * nProc: number of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum workload using this assignment method
 */
int bestWorkload(int *processors, int nProc, int *tasks, int taskCount) {
    int i; /* index counter */
    int idx; /* index of least workload processor */
    int busiestProcessorWorkloadThatMinimizesMaximum; /* busiest proc for which adding task minimizes max workload */
    int currentMaxWorkload = 0; /* current maximum workload */

    for(i = 0; i < taskCount; i++) {
        idx = getLeastWorkloadProcessorIndex(processors, nProc);

        if(processors[idx] + tasks[i] >= currentMaxWorkload) {
           currentMaxWorkload = processors[idx] + tasks[i];
	       processors[idx] += tasks[i];
        }
	   else {
	    busiestProcessorWorkloadThatMinimizesMaximum = processors[0];
        for(int j = 0; j < nProc; j++) {
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

int bestWorkloadDecreasing(int *processors, int nProc, int *tasks, int taskCount) {
    int *sortedTasksDecreasing = quicksort(tasks, taskCount);
    return bestWorkload(processors, nProc, sortedTasksDecreasing, taskCount);
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

int* quicksort(int *tasks, int taskCount) {
    qsort(tasks, taskCount, sizeof(int), comparatorFn);
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

