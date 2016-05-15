
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
#include "/c/cs223/Hwk3/getLine.h"

#define MAX_NUM_WORDS 100
#define ALPHABET_SIZE 26

void initializeNode(trieNodePtr t) {
  for (int i = 0; i<ALPHABET_SIZE; i++) t->children[i] = NULL;
  t->isTerminal = t->used = false;
}

void insert(trieNodePtr root, char *string) {
  int pos;
  trieNodePtr child;

  for(int i = 0; i<strlen(string); i++) {
    pos = string[i] - 'a';
    child = root->children[pos];
    if(!child) {
      child = (trieNodePtr) malloc(sizeof(trieNode));
      initializeNode(child);
      root->children[pos] = child;
    }
    root = child;
    if(i == strlen(string)-1) {
      root->isTerminal = true;
    }
  }
}

int trieNodeHasChildren(trieNodePtr t) {
 for (int i=0; i<ALPHABET_SIZE; i++) {
   if (t->children[i] != NULL) {
     return true;
   }
 }
 return false;
}

int search(trieNodePtr root, char *string) {
  
}


int main(int argc, char *argv[]) {

  int intArg; /* current arg as int */
  int NROWS = 0; /* ARG: number of board rows */
  int NCOLS = 0; /* ARG: number of board columns */
  int histogram[MAX_NUM_WORDS]; /* word counts */
  bool showNonBoggle = false; /* ARG: flag to print non-Boggle words */
  bool useLettersOnce = false; /* ARG: flag to only use letters once */
  bool isValid; /* flag to signify stdin word (dictionary entry) is valid */
  char *board = NULL; /* ARG: board */
  char *input = NULL; /* STDIN: dictionary word */

  // check for valid argument count
  if(argc < 4 || argv > 6) {
    fprintf(stderr, "Usage: %s filename. Invalid number of arguments: %d.", argv[0], argc);
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0) {
        showNonBoggle = true;
      } else if (intArg == 0) {
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    } else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0) {
        useLettersOnce = true;
      } else if (intArg == 0){
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    } else if(i == argc-1) {
      if(intArg == 0 && !board && strlen(argv[i]) >= NROWS * NCOLS) {
        board = argv[i];
      } else {
        fprintf(stderr, "Usage: %s filename. Invalid board argument: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    } else {
      if(NROWS == 0 && intArg > 0) {
        NROWS = intArg;
      } else if(NCOLS == 0 && intArg > 0) {
        NCOLS = intArg;
      } else {
        fprintf(stderr, "Usage: %s filename. Invalid board dimension argument: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }

  // ensure we have necessary setup
  if(NROWS <= 0 || NCOLS <= 0 || !board) {
    fprintf(stderr, "Usage: %s filename. Error occurred with Boggle setup.", argv[0])
    exit(EXIT_FAILURE);
  }

  createBoard(board);
  // create trie here
  // create hash table

  // read words from stdin
  while((input = getLine(stdin)) != NULL) {
     // reset isValid flag
     isValid = true;

     // make sure strings are null-terminated
     if(input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';

     // check to make sure all characters are valid
     for(int j = 0; j < strlen(input); j++) {
       if(!isalpha(input[j])) {
         isValid = false;
       }
     }

     // skip to next word in dictionary if this one contains non-alphabetical characters
     if (!isValid) {
       continue;
     }

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
