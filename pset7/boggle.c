
/*
File: boggle.c
Description: This file contains a program that can be used to list every word in the standard input that is a "Boggle
word" for the NROWS x NCOLS array BOARD.
Name: Harrison Miller, hmm29
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "boggle.h"
#include "hash.h"
#include "/c/cs223/Hwk3/getLine.h"

#define MAX_LINE 100
#define ALPHA_SIZE 26

int main(int argc, char *argv[]) {
  int intArg; /* current arg as int */
  int NROWS = 0; /* number of board rows */
  int NCOLS = 0; /* number of board columns */
  bool showNonBoggle = false; /* flag: print non-Boggle words */
  bool useLettersOnce = false; /* flag: only use letters once */
  char *board = NULL; /* board */
  char *input = NULL; /* stdin word */

  // need board

  // check for valid argument count
  if(argc < 4 || argv > 6) {
    fprintf(stderr, "Usage: %s filename\nInvalid number of arguments: %d.", argv[0], argc)
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0) {
        showNonBoggle = true;
      } else if (intArg == 0) {
        fprintf(stderr, "Usage: %s filename\nInvalid flag: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    } else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0) {
        useLettersOnce = true;
      } else if (intArg == 0){
        fprintf(stderr, "Usage: %s filename\nInvalid flag: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    } else if(i == argc-1) {
      if(intArg == 0 && !board && strlen(argv[i]) >= NROWS * NCOLS) {
        board = argv[i];
      } else {
        fprintf(stderr, "Usage: %s filename\nInvalid board argument: %s.", argv[0], argv[i])
        exit(EXIT_FAILURE);
      }
    } else {
      if(NROWS == 0 && intArg > 0) {
        NROWS = intArg;
      } else if(NCOLS == 0 && intArg > 0) {
        NCOLS = intArg;
      }
    }
  }

  // create trie here
  // create hash table

  if(NROWS <= 0 || NCOLS <= 0 || !board || !table) {
    fprintf(stderr, "Usage: %s filename\nError occurred with Boggle setup.", argv[0])
    exit(EXIT_FAILURE);
  }

  // read words from stdin
  while((input = getLine(stdin)) != NULL) {
     if(input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';

     // traverse trie
     for(int i = 0; i < strlen(input); i++) {
       // if key is '_', then move to next letter in input
       // if -t flag specified, keep track of whether or not trie node key has been used or not
     }

     // if it's a boggle word -> key: hash(input), value: 1
     // else if key already there then increment value by 1
     // else -> key: hash(input), value: 0

     // if -c flag specified then also put non-boggle words into hash table
   }

   // sort the hash table with radix sort
   // print values using specified format

   // free everything here

  return EXIT_SUCCESS;
}
