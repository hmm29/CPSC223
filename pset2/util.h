/*
File: util.h
Description: This file contains function prototypes for the helper/utility functions used in util.c and Psched.c.
Name: Harrison Miller, hmm29
*/

/* gets number of tasks */
int getTaskCount(int argc, char **argv);

/* gets number of flags */
int getFlagCount(int argc, char **argv, int taskCount);

/* calculates the minimized maximum workload using assignment specified by flag argument */
int getMaxWorkLoad(int *processors, int nProc, int *tasks, int taskCount, char *flag);

/* uses backtracking to find assignment for minimizing the maximum workload */
int backtrackToOpt(int *processors, int nProc, int *tasks, int taskCount);

/* assigns tasks in order they appear, greedily choosing processor with least workload at the time */
int leastWorkload(int *processors, int nProc, int *tasks, int taskCount);

/* sorts task runtimes in decreasing order and then uses least workload heuristic */
int leastWorkloadDecreasing(int *processors, int nProc, int *tasks, int taskCount);

/* assign tasks in order they appear, greedily choosing busiest processor for which the assignment
 * would not increase the current maximum workload */
int bestWorkload(int *processors, int nProc, int *tasks, int taskCount);

/* sort task runtimes in decreasing order and then use best workload heuristic */
int bestWorkloadDecreasing(int *processors, int nProc, int *tasks, int taskCount);

/* compare values in quicksort */
int comparatorFn(const void *a, const void *b);

/* divide-and-conquer sorting algorithm */
int* quicksort(int *tasks, int taskCount);

/* get index of processor with the least current workload */
int getLeastWorkloadProcessorIndex(int *processors, int nProc);

/* get index of processor with greatest current workload */
int getMaxWorkloadProcessorIndex(int *processors, int nProc);
