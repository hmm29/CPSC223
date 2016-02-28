
/*
File: Psched.c
Description: This file contains a program for processor scheduling that performs various assignments of
tasks to processors and prints their maximum workloads.
Name: Harrison Miller, hmm29
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int main(int argc, char *argv[]) {

    static int nProc; /* number of processors */
    static int maxWorkLoad; /* maximum workload among processors */
    static int *processors; /* array of processors */
    static int *tasks; /* array of tasks */
    static char **flags; /* array of flag strings */
    static int flagCount; /* number of flags */
    static int taskCount; /* number of tasks */

    // check for the valid argument count
    if(argc < 2) {
        fprintf(stderr, "Usage: %d filename\nInvalid number of arguments: %s", argc, argv[0]);
        exit(1);
    }

    if(argc == 2) {
      return EXIT_SUCCESS;
     }
    
    // ensure that a valid number of processors provided
    if(argc >= 2 && atoi(argv[1]) > 0) {
       nProc = atoi(argv[1]);
       processors = malloc(nProc * sizeof(int));
    } else {
        fprintf(stderr, "Usage: %s filename\nInvalid number of processors.", argv[0]);
        exit(1);
    }

   // set all elements in processor array to zero
   int j;
   for(j = 0; j < nProc; j++) {
    processors[j] = 0;
   }

   tasks = getTasks(argc, argv);       /* get an array of tasks based on taskRuntime inputs */
   flags =  getFlags(argc, argv);       /* get array of flags based on flag input */

    taskCount = getTaskCount();
    flagCount = getFlagCount();
    
   //if no tasks or flags, then exit gracefully
    if(taskCount == 0 || flagCount == 0) {
       return EXIT_SUCCESS;
    }

    for(int i = 0; i < flagCount; i++) {
        maxWorkLoad = getMaxWorkLoad(processors, nProc, tasks, flags[i]);
        printf("%-4s %d\n", flags[i], maxWorkLoad);
        int j;
	
	// must rest tasks if they have been sorted
        tasks = getTasks(argc, argv);
	
	// must reset processors to zero for each flag iteration
        for(j = 0; j < nProc; j++) {
 	   processors[j] = 0;
        }
    }

    return EXIT_SUCCESS;
}

