
/*
File: Boggle.c
Description: This file contains a program for processor scheduling that performs various assignments of
tasks to processors and prints their maximum WorkLoads.
Name: Harrison Miller, hmm29
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "boggle.h"
#include "/c/cs223/Hwk3/getLine.h"

#define MAX_LINE 100
#define ALPHA_SIZE 26
#define MAX_BOARD_SIZE 10

int main(int argc, char *argv[]) {
  int intArg; /* current argument as integer */
  int NROWS; /* number of rows */
  int NCOLS; /* number of columns */
  bool showNonBoggle; /* non-Boggle words flag */
  bool useLettersOnce; /* only use letters once in Boggle */
  char *input; /* stdin word */
  // need board

  // initializations
  showNonBoggle = useLettersOnce = false;

  // check for valid argument count
  if(argc < 4 || argv > 6) {
    printf("Usage: %s filename\nInvalid number of arguments: %d.", argv[0], argc)
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0) {
        showNonBoggle = true;
      } else if (intArg == 0) {
        printf("Usage: %s filename\nInvalid flag: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    }
    else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0) {
        useLettersOnce = true;
      } else if (intArg == 0){
        printf("Usage: %s filename\nInvalid flag: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    }
    else if(i == argc-1) {
      if(intArg == 0 && strlen(argv[i]) >= NROWS * NCOLS) {
        // board
      } else {
        printf("Usage: %s filename\nInvalid argument: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      }
    } else {
      if(NROWS == 0) {
        NROWS = intArg;
      } else if(NCOLS == 0) {
        NCOLS = intArg;
      }
    }
  }

  // create boggle board here

  if(NROWS <= 0 || NCOLS <= 0 || !board) {
    printf("Usage: %s filename\nError occurred with Boggle board values.", argv[0])
    exit(EXIT_FAILURE);
  }

  while((input = getLine(stdin)) != NULL) {
     if(input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';


   }
   // free rules
   for(int r = 0; r < numRules; r++) {
       free(rules[r]);
   }


  return EXIT_SUCCESS;
}
