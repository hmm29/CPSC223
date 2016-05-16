
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

char *getWord(FILE *fp) {
  int c = 0;
  char *in = getLine(fp);
  removeNewline(in);
  while(*in) {
      c = tolower(*in);
      *in++ = c;
   }
   return in;
}

void removeNewline(char *str) {
  while(*str && *str != '\n' && *str != '\r') str++;
  *str = 0;
}

int isValidWord(char *str) {
  int c = 0;1
  if(str[strlen(str)-1] == '\n') removeNewline(str);
  if (strlen(str) < 3) return 0;
  while(*str) {
    c = tolower(*str);
    if (!(c >= 'a' && (c <= 'z'))) return 0;
    *str++ = c;
  }
  return 1;
}

trieNodePtr makeNode(void) {
  trieNodePtr t = (trieNodePtr) malloc(sizeof(trieNode));
  for (int i = 0; i < ALPHABET_SIZE; i++) t->children[i] = NULL;
  t->count = 0;
  return t;
}

void insertWord(trieNodePtr root, char *word) {
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
  }
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

void traverseUtil(boardPtr board, trieNodePtr trie, int row, int col, int seen[], char* word, int noReuse) {
  int nrow, ncol;
  char newWord[board->NROWS * board->NCOLS]; // max word size
  int nseen[board->NROWS * board->NCOLS];

  for(int i = 0; i < board->NROWS * board->NCOLS; i++) nseen[i] = seen[i]; // update seen marker grid

  // check all letters around current position
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      nrow = row + i;
      ncol = col + j;
      // if neighbor position is valid, then add to word
      if (nrow >= 0 && nrow < board->NROWS && ncol >= 0 && ncol < board->NCOLS) {
        // if noReuse flag, ensure that neighbor has not been visited
        if(noReuse && seen[nrow * board->NROWS + ncol] == 0) {
          sprintf(newWord,"%s%c",word,board->grid[nrow][ncol]);
          seen[nrow * board->NROWS + ncol] = 1;
          traverseUtil(board, trie, nrow, ncol, nseen, newWord, noReuse);
        } else if (!noReuse) {
          sprintf(newWord, "%s%c", word, board->grid[nrow][ncol]);
          seen[nrow * board->NROWS + ncol] = 1;
          traverseUtil(board, trie, nrow, ncol, nseen, newWord, noReuse);
        }
      }
    }
  }
}

void traverse(boardPtr board, trieNodePtr trie, int noReuse) {
  char word[board->NROWS * board->NCOLS];
  int seen[board->NROWS * board->NCOLS];
        
  for (int row = 0; row < board->NROWS; row++) {
    for (int col = 0; col < board->NCOLS; col++) {
        for (int i = 0; i < board->NROWS * board->NCOLS; i++) seen[i] = 0; // initialize all to 0
        seen[(row * board->NROWS) + col] = 1; // mark current letter as seen
        sprintf(word,"%c",board->grid[row][col]); // replace word with this letter
        traverseUtil(board, trie, row, col, seen, word, noReuse);
    }
  }
}

void printWords(trieNodePtr trie, int showNonBoggleWords) {
  int i;
  if (root == NULL) return;

  if(showNonBoggleWords && root->count == 0) {
    printf("%s\n", word);
  }

  if (root->count > 0) {
    printf("%s: %d\n", word, root->count);
  }

  for (i = 0; i < ALPHABET_SIZE; i++)
  {
      printWords(root->children[i], showNonBoggleWords);
  }
}

void clearTrie(trieNodePtr root){
  if (root){
    free(root);
    for (int i = 0; i < ALPHABET_SIZE; i++) clearTrie(root->children[i]);
  }
}

int main(int argc, char *argv[]) {

  int intArg; /* current arg as int */
  int NROWS = 0; /* ARG: number of board rows */
  int NCOLS = 0; /* ARG: number of board columns */
  int showNonBoggleWords = 0; /* ARG: flag to print all non-Boggle words */
  int noReuse = 0; /* ARG: flag to only use letters once */
  char *letters = NULL; /* ARG: board letters */
  char *input = NULL; /* STDIN: dictionary word */

  // check for valid argument count
  if(argc < 4 || argc > 6) {
    fprintf(stderr, "Usage: %s filename. Invalid number of arguments: %d.\n", argv[0], argc);
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0) {
        showNonBoggleWords = 1;
      } else if (intArg == 0) {
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    } else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0) {
        noReuse = 1;
      } else if (intArg == 0){
        fprintf(stderr, "Usage: %s filename. Invalid flag: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    } else if(i == argc-1) {
      if(intArg == 0 && !letters && strlen(argv[i]) == NROWS * NCOLS) {
        letters = argv[i];
      } else {
        fprintf(stderr, "Usage: %s filename. Invalid board argument: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    } else {
      if(NROWS == 0 && intArg > 0) {
        NROWS = intArg;
      } else if(NCOLS == 0 && intArg > 0) {
        NCOLS = intArg;
      } else {
        fprintf(stderr, "Usage: %s filename. Invalid board dimension argument: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }

  // ensure we have necessary setup
  if(NROWS < 1 || NCOLS < 1 || !letters) {
    fprintf(stderr, "Usage: %s filename. Error occurred with Boggle setup.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // make board
  boardPtr board = makeBoard(NROWS, NCOLS, letters);

  // make trie
  trieNodePtr root = makeNode();

  // read words from stdin
  while((input = getWord(stdin)) != NULL) {
     // if not then simply skip
     if (!isValidWord(input)) {
       continue;
     }

     insertWord(root, input);
   }

   // walk board and count words
   traverse(board, root, noReuse);
   printWords(root, showNonBoggleWords);

   // free heap storage
   free(board);
   clearTrie(root);

  return EXIT_SUCCESS;
}
