#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

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
 * Function: comparatorFnDesc
 * ---------------------
 * compares values to be in descending order
 *
 * a: pointer to first val for comparison
 * b: pointer to second val for comparison
 *
 * returns: the sorted input array, with elements in order specified by order argument
 */

int comparatorFnDesc (const void *a, const void *b)
{
    return *(int*)b-*(int*)a;
}

/*
 * Function: comparatorFnAsc
 * ---------------------
 * compares values to be in ascending order
 *
 * a: pointer to first val for comparison
 * b: pointer to second val for comparison
 *
 * returns: the sorted input array, with elements in order specified by order argument
 */

int comparatorFnAsc (const void *a, const void *b)
{
    return *(int*)a-*(int*)b;
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

int* quicksort(int *tasks, int taskCount, char *order) {
    if(strcmp(order, "desc") == 0) {
            qsort(tasks, taskCount, sizeof(int), comparatorFnDesc);
    } else if (strcmp(order, "asc") == 0) {
            qsort(tasks, taskCount, sizeof(int), comparatorFnAsc);
    } else {
        printf("Usage: %s filename\nInvalid flag(s). Flags must be one of the following: -opt, -lw, -lwd, -bw, or -bwd.", argv[0]);
    }
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

