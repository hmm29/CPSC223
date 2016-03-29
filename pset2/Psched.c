/*
File: Psched.c
Description: This file contains a program for processor scheduling that performs various assignments of
tasks to processors and prints their maximum WorkLoads.
Name: Harrison Miller, hmm29
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

int main(int argc, char *argv[]){

  int arg; /* current argument */
  int nProc; /* num of processors */
  int taskCount; /* num of tasks */
  bool isFlag; /* marker for whether arg is flag or not */
  int maxWorkLoad; /* maxWorkLoad for an assignment method */
  int tasks[argc]; /* store tasks in this array */
  int sortedTasks[argc]; /* another array to store sorted tasks */

  taskCount = 0;
  isFlag = false;

  // @hmm: check for the valid argument count
  if(argc < 2) {
      printf("Usage: %d filename\nInvalid number of arguments: %s", argc, argv[0]);
      exit(EXIT_FAILURE);
  }

  // @hmm: if no tasks AND no flags, exit gracefully
  if(argc == 2) {
    return EXIT_SUCCESS;
   }

  // @hmm: process the arguments, starting at idx 1
  // main for loop to do this
  for (int i = 1; i < argc; i++){

      arg = atoi(argv[i]);
      
      if (i == 1 && arg > 0) {
        nProc = atoi(argv[1]);
      }

      else if (i == 1){
        printf("Usage: %s filename\nInvalid number of processors.", argv[0]);
        return EXIT_FAILURE;
      }

      else if (arg < 0){
        printf("Usage: %s filename\nArguments must be non-negative.", argv[0]);
        return EXIT_FAILURE;
      }

      else if (arg > 0 && !isFlag){
        tasks[i-2] = arg;
        sortedTasks[i-2] = arg;
        taskCount++;
      }

      else if(arg == 0) {
        if (strcmp(argv[i], "-opt") == 0){
          isFlag = true;
          maxWorkLoad = backtrackToOpt(nProc, tasks, taskCount);
          printf("-opt %d\n", maxWorkLoad);
        }

        else if (strcmp(argv[i], "-lw") == 0){
          isFlag = true;
          maxWorkLoad = leastWorkLoad(nProc, tasks, taskCount);
          printf("-lw  %d\n", maxWorkLoad);
        }

        else if (strcmp(argv[i], "-lwd") == 0){
          isFlag = true;
          quicksort(sortedTasks, taskCount, "desc");
          maxWorkLoad = leastWorkLoad(nProc, sortedTasks, taskCount);
          printf("-lwd %d\n", maxWorkLoad);
        }

        else if (strcmp(argv[i], "-bw") == 0){
          isFlag = true;
          maxWorkLoad = bestWorkLoad(nProc, tasks, taskCount);
          printf("-bw  %d\n", maxWorkLoad);
        }

        else if (strcmp(argv[i], "-bwd") == 0){
          isFlag = true;
          quicksort(sortedTasks, taskCount, "desc");
          maxWorkLoad = bestWorkLoad(nProc, sortedTasks, taskCount);
          printf("-bwd %d\n", maxWorkLoad);
        }

        else {
          printf("Usage: %s filename\nInvalid flag(s). Flags must be one of the following: -opt, -lw, -lwd, -bw, or -bwd.\n", argv[0]);
          return EXIT_FAILURE;
        }
      }
    }

    return EXIT_SUCCESS;
  }