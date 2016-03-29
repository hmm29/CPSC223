#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

/*
 * Function: backtrackToOpt
 * ------------------------
 * Uses backtracking to find an assignment that minimizes maximum WorkLoad among processors
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum WorkLoad using this assignment method
 */

int backtrackToOpt(int nProc, int *tasks, int taskCount) {	

  int upperBound; /* lower bound on tasks */
  int lowerBound; /* upper bound on tasks */
  int arrSum; /* sum of tasks in array */
  int res; /* result of backtrack */
  int processors[nProc]; /* array of processors */

  for (int i = 0; i < nProc; i++)
    processors[i] = 0;

  // @hmm: sort workLoad by decreasing order in order to compute the intial upper bound using -lwd
  quicksort(tasks, taskCount, "desc");
  upperBound = leastWorkLoad(nProc, tasks, taskCount);

  arrSum = sum(tasks, taskCount);

  // @hmm: compute lower bound
  lowerBound = arrSum/nProc + (arrSum % nProc != 0);
  res = backtrack(lowerBound, upperBound, nProc, processors, taskCount, tasks, tasks, 0, 0);
  return res;
}

int backtrack(int lowerBound, int upperBound, int nProc, int processors[], int taskCount, int tasks[], int prevTasks[], int numTasksRemaining, int prevProcessorIdx) {
    // @hmm: base case: if no more tasks left then return maxWorkLoad or the upper bound, which one is smaller
  if (taskCount == 0) {
    int largest = maxElement(processors, nProc);
    return (largest < upperBound) ? largest : upperBound;
  }

  for (int j = 0; j < nProc; j++){
    if (upperBound == lowerBound) {
      return lowerBound;
    }

    processors[j] += tasks[numTasksRemaining];
    if (j > 0 && (processors[j] - tasks[numTasksRemaining] == processors[j - 1])){
      processors[j] -= tasks[numTasksRemaining];
      continue;
    }
    else if (processors[j] >= upperBound){
      processors[j] -= tasks[numTasksRemaining];
      continue;
    }
    else if ((j > 0) && (prevTasks[numTasksRemaining - 1] == tasks[numTasksRemaining]) && j < prevProcessorIdx){
      processors[j] -= tasks[numTasksRemaining];
      continue;
    }
    else {
      int backtrackLower = backtrack(lowerBound, upperBound, nProc, processors, taskCount-1, tasks, prevTasks, numTasksRemaining + 1, j);
      if (backtrackLower < upperBound)
        upperBound = backtrackLower;
    }
    // @hmm: remove task from the current processor[index]
    processors[j] -= tasks[numTasksRemaining];
  }
  return upperBound;
}

/*
 * Function: leastWorkLoad
 * -----------------------
 * assigns tasks in order they appear, greedily choosing processor with least WorkLoad
 *
 * processors: array of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum WorkLoad using this assignment method
 */

int leastWorkLoad(int nProc, int *tasks, int taskCount) {  
    int processors[nProc]; /* number of processors */
    int idx = 0; /* current index in array */

    for (int i = 0; i < nProc; i++) processors[i] = 0;

    for(int i = 0; i < taskCount; i++) {
        idx = getLeastWorkLoadProcessorIndex(processors, nProc); // get index of least WorkLoad processor
        processors[idx] += tasks[i]; /* assign the task to the least WorkLoad processor */
    }

    idx = getMaxWorkLoadProcessorIndex(processors, nProc);
    // printf("at index %d the val is %d hahah\n", idx, processors[idx]);
    return processors[idx];
}

/*
 * Function: bestWorkLoad
 * ----------------------
 * assign tasks in order they appear, greedily choosing busiest processor for which the assignment
 * would not increase the maximum WorkLoad
 *
 * processors: array of processors
 * nProc: number of processors
 * tasks: array of task runtimes
 * taskCount: number of task runtimes
 *
 * returns: value of maximum WorkLoad using this assignment method
 */
int bestWorkLoad(int nProc, int *tasks, int taskCount) {
    int idx; /* index of least WorkLoad processor */
    int busiestProcessorWorkLoadThatMinimizesMaximum; /* busiest proc for which adding task minimizes max WorkLoad */
    int currMaxWorkLoad = 0; /* current maximum WorkLoad */
    int processors[nProc]; /* array of processors */

    for (int i = 0; i < nProc; i++)
    processors[i] = 0;

    for(int i = 0; i < taskCount; i++) {
        idx = getLeastWorkLoadProcessorIndex(processors, nProc);

        if(processors[idx] + tasks[i] >= currMaxWorkLoad) {
           currMaxWorkLoad = processors[idx] + tasks[i];
	       processors[idx] += tasks[i];
        }
	   else {
	    busiestProcessorWorkLoadThatMinimizesMaximum = processors[0];
        for(int j = 0; j < nProc; j++) {
		if((processors[j] + tasks[i] <= currMaxWorkLoad) && (busiestProcessorWorkLoadThatMinimizesMaximum <= processors[j])) {
			busiestProcessorWorkLoadThatMinimizesMaximum = processors[j];
			idx = j;
		} 
	    }
	    processors[idx] += tasks[i];
        }
    }

    idx = getMaxWorkLoadProcessorIndex(processors, nProc);
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
        printf("Invalid order scheme in quicksort.");
    }
    return tasks;
}

/*
 * Function: getLeastWorkLoadProcessorIndex
 * ----------------------------------------
 * get index of processor with lowest WorkLoad
 *
 * processors: array of processors, whos WorkLoads are int values
 * nProc: num of processors
 *
 * returns: the index of the processor with the least WorkLoad
 */

int getLeastWorkLoadProcessorIndex(int processors[], int nProc) {
    int idx = 0; /* index */
    int minimum = processors[0]; /* minimum element in arr */

    for (int i = 1 ; i < nProc; i++)
    {
        if ( processors[i] < minimum )
        {
            minimum = processors[i];
            idx = i;
        }
    }
    return idx;
}

/*
 * Function: getMaxWorkLoadProcessorIndex
 * ----------------------------------------
 * get index of processor with highest WorkLoad
 *
 * processors: array of processors, whos WorkLoads are int values
 * nProc: num of processors
 *
 * returns: the index of the processor with the least WorkLoad
 */
int getMaxWorkLoadProcessorIndex(int processors[], int nProc) {
	int idx = 0; /* index */
	int maximum = processors[0]; /* maximum element in array */

	for(int i = 1; i < nProc; i++) {
	  if(processors[i] > maximum){
	      maximum = processors[i];
	      idx = i;
	  }
  	}
	return idx;
}

/*
 * Function: maxElement
 * ----------------------------------------
 * get largest element in an array
 *
 * arr: array of values
 * length: length of array
 *
 * returns: largest elemnt in the array
 */
int maxElement(int arr[], int length){
  int currMax; /* running current maximum elemnt */

  currMax = 0;
  for (int i = 0; i < length; i++){
    if (arr[i] > currMax)
      currMax = arr[i];
  }
  return currMax;
}

/*
 * Function: sum
 * ----------------------------------------
 * get sum of elements in an array
 *
 * arr: array of values
 * length: length of array
 *
 * returns: sum of elements in the array
 */
int sum(int arr[], int length){
  int sum; /* sum of elts in array */

  sum = 0;

  for (int i = 0; i < length; i++) {
    sum += arr[i];
  }

  return sum;
}


