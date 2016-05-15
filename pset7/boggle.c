
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
#include "boggle.h"
#include "/c/cs223/Hwk3/getLine.h"

trieNodePtr makeNode(void) {
  trieNodePtr t = (trieNodePtr) malloc(sizeof(trieNode));
  for (int i = 0; i < ALPHABET_SIZE; i++) t->children[i] = NULL;
  t->isTerminal = t->used = 0;
  t->count = 0;
}

void insert(trieNodePtr root, char *word) {
  int pos; /* position of char in node children array */
  trieNodePtr child; /* child node of current trie node */

  for(int i = 0; i < strlen(word); i++) {
    pos = tolower(word[i]) - 'a';
    child = root->children[pos];
    if(!child) {
      child = makeNode();
      root->children[pos] = child;
    }
    root = child;
    if(i == strlen(string)-1) {
      root->isTerminal = 1;
    }
  }
}

char *getWord(File fp) {
  char* in = getLine(File fp);
  removeNewline(in);
  while(*in) {
      c = tolower(*in);
      *in++ = c;
   }
}

void removeNewline(char *str) {
  while(*str && *str != '\n' && *str != '\r') str++;
  *str = 0;
}

int isValidWord(char *str) {
  int c = 0;
  removeNewline(str);
  if (strlen(str) < 3) return 0;
  while(*str) {
    c = tolower(*str);
    if (!(c >= 'a' && (c <= 'z'))) return 0;
    *str++ = c;
  }
  return 1;
}

boardPtr makeBoard(int NROWS, int NCOLS, char *letters) {
  boardPtr board = (boardPtr) malloc(sizeof(board));
  board->NROWS = NROWS;
  board->NCOLS = NCOLS;

  for(int i = 0; i < NROWS; i++) {
    for(int j = 0; j < NCOLS; j++) {
      board->grid[i][j] = letters[i * NROWS + j];
    }
  }
  return board;
}

void traverse(boardPtr board, trieNodePtr t, int row, int col) {
  for (int row=0; row < board->NROWS; row++) {
    for (int col=0; col < board->NCOLS; col++) {
      traverse(board,trie,row,col);
    }
  }
}

int clearTrie (trieNodePtr root){
  if (root){
    free(root);
    for (int i = 0; i < ALPHABET_SIZE; i++) clearTrie(root->children[i]);
  }
}

int main(int argc, char *argv[]) {

  int intArg; /* current arg as int */
  int NROWS = 0; /* ARG: number of board rows */
  int NCOLS = 0; /* ARG: number of board columns */
  int icount = 0; /* count of stdin inputs */
  int showNonBoggleWords = 0; /* ARG: flag to print non-Boggle words */
  int noReuse = 0; /* ARG: flag to only use letters once */
  char *board = NULL; /* ARG: board */
  char *input = NULL; /* STDIN: dictionary word */
  char *dict[MAX_NUM_WORDS]; /* array of inputs */

  // check for valid argument count
  if(argc < 4 || argv > 6) {
    fprintf(stderr, "Usage: %s filename. Invalid number of arguments: %d.", argv[0], argc);
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0) {
        showNonBoggleWords = 1;
      } else if (intArg == 0) {
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    } else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0) {
        noReuse = 1;
      } else if (intArg == 0){
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    } else if(i == argc-1) {
      if(intArg == 0 && !board && strlen(argv[i]) == NROWS * NCOLS) {
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
  if(NROWS < 1 || NCOLS < 1 || !board) {
    fprintf(stderr, "Usage: %s filename. Error occurred with Boggle setup.", argv[0])
    exit(EXIT_FAILURE);
  }

  boardPtr board = makeBoard(NROWS, NCOLS, board);

  // make trie
  trieNodePtr root = makeNode();
  root->isTerminal = 1;

  // read words from stdin
  while((input = getWord(stdin)) != NULL) {
     icount++;

     // if not then simply skip
     if (!isValidWord(input)) {
       continue;
     }

     insertWord(root, input);
   }

   // walk board and count words
   traverse(board, root, 0, 0);
   printWords(root);

   // free heap storage
   free(board);
   clearTrie(root);

  return EXIT_SUCCESS;
}
