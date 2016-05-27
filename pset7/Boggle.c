
/******************************************************************************
 * Boggle.c
 * This file contains a program that can be used to list every word in the
 * standard input that is a "Boggle word" for the NROWS x NCOLS array BOARD.
 *
 * Harrison Miller
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Boggle.h"

/*
 *  Function: getWord
 *  --------------------
 *  reads and parses words from FILE object
 *
 *  fp: file stream
 *
 *  returns: word to lower case with terminal newlines removed
 */

char *getWord(FILE *fp) {
    char *input;
    int size = 8;
    int c, i = 0;

    input = malloc(size);
    while((c = getc(fp)) != EOF) {
        if (c == '\n') {
          if(i == 0) {
      	   	continue;
      	  } else {
          	break;
     	    }
    }
  	if(i == size-1) {
  	   size *= 2;
  	   input = realloc(input, size);
  	}
	  input[i++] = tolower(c);
    }
    if (c == EOF && i == 0)  {
        free(input);
        return NULL;
    }
    input[i++] = '\0';
    input = realloc(input, i);
    return input;
}

/*
 *  Function: isValidWord
 *  --------------------
 *  reads and parses words from stdin
 *
 *  str: string to be checked
 *
 *  returns: whether string is a valid input
 */

int isValidWord(char *str) {
  int c = 0;
  if(!str || !isalpha(*str)) return 0;
  while(*str) {
    c = tolower(*str++);
    if(!isalpha(c)) return 0;
    if (!(c >= 'a' && (c <= 'z'))) return 0;
  }
  return 1;
}

/*
 *  Function: makeNode
 *  --------------------
 *  makes and initializes a new trie node
 *
 *  returns: pointer to the new trie node
 */

trieNodePtr makeNode(void) {
  trieNodePtr t = (trieNodePtr) malloc(sizeof(TrieNode));

  if(!t) return NULL;

  for (int i = 0; i < ALPHABET_SIZE; i++) t->children[i] = NULL;
  t->count = 0;
  t->word = NULL;

  return t;
}

/*
 *  Function: insertWord
 *  --------------------
 *  inserts word from stdin into trie
 *
 *  root: root of the trie
 *  word: string to be inserted
 *
 */

void insertWord(trieNodePtr root, char *word) {
  int pos; /* position of char in node children array */
  trieNodePtr child; /* child node of current trie node */

  if(!root) root = makeNode();

  for(int i = 0; i < strlen(word); i++) {
    pos = tolower(word[i])-'a';
    child = root->children[pos];

    if(!child) {
      child = makeNode();
      root->children[pos] = child;
    }
    root = child;
    // if at the end of the word (i = strlen-1)
    // and root->word is null, root->word = word
    if(i == strlen(word)-1 && !root->word) {
      root->word = word;
      return;
    }
  }
}

/*
 *  Function: makeBoard
 *  --------------------
 *  makes and initializes a new Boggle board
 *
 *  NROWS: number of rows
 *  NCOLS: number of columns
 *  letters: board characters as one-dimensional string
 *
 *  returns: pointer to the new Boggle board
 */

boardPtr makeBoard(int NROWS, int NCOLS, char *letters) {
  boardPtr board = (boardPtr) malloc(sizeof(Board));

  if(!board) return NULL;

  board->NROWS = NROWS;
  board->NCOLS = NCOLS;

  for(int i = 0; i < NROWS * NCOLS; i++) {
     board->grid[i] = tolower(letters[i]); // 1D board
  }
  return board;
}

/*
 *  Function: traverse
 *  --------------------
 *  walk the Boggle board
 *
 *  board: the Boggle board
 *  trie: the trie of input words
 *  noReuse: flag to indicate whether board letters can be revisited
 *
 */

void traverse(boardPtr board, trieNodePtr trie, int idx, int row, int col, int next[], int n, int noReuse) {
  int nextRow, nextCol, p, c, nextPos, seen;
  char nextLetter;

  if(!board || !trie) return;

  trie->count++; // increment count

  // ensure next row is valid
  nextRow = row+1;
  nextRow = (nextRow >= board->NROWS) ? board->NROWS-1 : nextRow;
  nextCol = col+1;
  nextCol = (nextCol >= board->NCOLS) ? board->NCOLS-1 : nextCol;

  p = row-1;
  p = (p < 0) ? 0 : p;

  while(p <= nextRow) {
    // ensure next column is valid
    c = col-1;
    c = (c < 0) ? 0 : c;
    while(c <= nextCol){
      nextPos = p * board->NROWS + c;
      if (nextPos == idx) continue;  // skip if we get back to same time
      if (noReuse) {
        seen = 0;
        for(int l = 0; l < n; l++) {
          if (next[l] == nextPos) {
            seen = 1;
            break;
          }
        }
        if (seen) {
          continue;
        }
      }
      int updatedNext[n + 1];
      for (int i = 0; i < n; i++) { // copy over next next options list
        updatedNext[i] = next[i]; 
      }
      updatedNext[n] = nextPos;
      nextLetter = board->grid[nextPos];
      // traverse again using character logic
      if (nextLetter == '_') { // wildcard
        for (int i = 0; i < ALPHABET_SIZE; i++) {
          traverse(board, trie->children[i], nextPos, p, c, updatedNext, n+1, noReuse);
        }
      } else { // non-wildcard
        int pos = nextLetter-'a';
        traverse(board, trie->children[pos], nextPos, p, c, updatedNext, n+1, noReuse);
      }
      c++;
    }
    p++;
  }
  return;
}

/*
 *  Function: printWords
 *  --------------------
 *  print trie words in alphabetical order
 *
 *  root: root of the trie
 *  showNonBoggleWords: flag to hide or print non-Boggle words
 *
 */
void printWords(trieNodePtr root, int showNonBoggleWords) {
  if (!root) return;

  // check that word exists
  if(showNonBoggleWords && root->count == 0 && root->word) {
    printf("%s\n", root->word);
  } else if (!showNonBoggleWords && root->count && root->word) {
    printf("%s: %d\n", root->word, root->count);
  }

  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    printWords(root->children[i], showNonBoggleWords);
  }

  return;
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
    fprintf(stderr, "Usage: %s. Invalid # of args: %d.\n", argv[0], argc);
    exit(EXIT_FAILURE);
  }

  // argument parsing
  for(int i = 1; i < argc; i++) {
    intArg = atoi(argv[i]);

    if(i == 1) {
      if(intArg == 0 && strcmp(argv[i], "-c") == 0 && !showNonBoggleWords) {
        showNonBoggleWords = 1;
      } else if (intArg == 0 && strcmp(argv[i], "-t") == 0 && !noReuse) {
        noReuse = 1;
      } else if (intArg == 0) {
        fprintf(stderr,"Usage: %s. Invalid flag: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NROWS = intArg;
      }
    } else if(i == 2) {
      if(intArg == 0 && strcmp(argv[i], "-t") == 0 && !noReuse) {
        noReuse = 1;
      } else if (intArg == 0 && strcmp(argv[i], "-c") == 0 && !showNonBoggleWords) {
        showNonBoggleWords = 1;
      } else if (intArg == 0){
        fprintf(stderr,"Usage: %s. Invalid flag: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      } else {
        NCOLS = intArg;
      }
    } else if(i == argc-1) {
      if(intArg == 0 && !letters && strlen(argv[i]) == NROWS * NCOLS) {
        letters = argv[i];
      } else {
        fprintf(stderr, "Usage: %s. Invalid arg: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    } else {
      if(NROWS == 0 && intArg > 0) {
        NROWS = intArg;
      } else if(NCOLS == 0 && intArg > 0) {
        NCOLS = intArg;
      } else {
        fprintf(stderr, "Usage: %s. Invalid arg: %s.\n", argv[0], argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }

  // ensure we have necessary setup
  if(NROWS < 1 || NCOLS < 1 || !letters) {
    fprintf(stderr, "Usage: %s. Error occurred with Boggle setup.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // make board
  boardPtr board = makeBoard(NROWS, NCOLS, letters);
  if(!board) {
    fprintf(stderr, "Usage: %s. Could not create board. \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // make trie
  trieNodePtr root = makeNode();
  if(!root) {
    fprintf(stderr, "Usage: %s. Could not create trie. \n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // read words from stdin
  while((input = getWord(stdin))) {
     if (!isValidWord(input)) {
      continue;
     }
     insertWord(root, input);
   }

   // walk board
   for(int row = 0; row < board->NROWS; row++) {
    for (int col = 0; col < board->NCOLS; col++) {
      int idx = row * board->NROWS + col;
      int next[] = { idx };

      char letter = board->grid[idx];
      int pos;

      // wildcard
      if (letter == '_') {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
          traverse(board, root->children[j], idx, row, col, next, 1, noReuse);
        }
      } else { // all other letters
        pos = letter-'a';
        traverse(board, root->children[pos], idx, row, col, next, 1, noReuse);
      }
    }
  }

   // print
   printWords(root, showNonBoggleWords);

  exit(EXIT_SUCCESS);
}
