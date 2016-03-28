/*
File: util.h
Description: This file contains function prototypes for the helper/utility functions used in util.c and Psched.c.
Name: Harrison Miller, hmm29
*/

/* uses backtracking to find assignment for minimizing the maximum workload */
int backtrackToOpt(int *processors, int nProc, int *tasks, int taskCount);

/* assigns tasks in order they appear, greedily choosing processor with least workload at the time */
int leastWorkload(int *processors, int nProc, int *tasks, int taskCount);

/* assign tasks in order they appear, greedily choosing busiest processor for which the assignment
 * would not increase the current maximum workload */
int bestWorkload(int *processors, int nProc, int *tasks, int taskCount);

/* compare values in quicksort for descending order */
int comparatorFnDesc(const void *a, const void *b);

/* compare values in quicksort for ascending order */
int comparatorFnAsc(const void *a, const void *b);

/* divide-and-conquer sorting algorithm */
int* quicksort(int *tasks, int taskCount, char *order);

/* get index of processor with the least current workload */
int getLeastWorkloadProcessorIndex(int *processors, int nProc);

/* get index of processor with greatest current workload */
int getMaxWorkloadProcessorIndex(int *processors, int nProc);
