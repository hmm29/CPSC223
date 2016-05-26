/******************************************************************************
 * Boggle.h
 * This file contains typedef declarations and function prototypes
 * for the functions defined and called in boggle.c.
 *
 * Harrison Miller
 ******************************************************************************/

 #ifndef BOGGLE_H
 #define BOGGLE_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <string.h>

 #define ALPHABET_SIZE 26
 #define MAX_BOARD_LENGTH 10

 typedef struct trieNode {
   struct trieNode *children[ALPHABET_SIZE];
   char *word;
   int count;
 } TrieNode;

 typedef struct trieNode *trieNodePtr;

 typedef struct board {
   int NROWS;
   int NCOLS;
   char grid[MAX_BOARD_LENGTH * MAX_BOARD_LENGTH];
 } Board;

 typedef struct board *boardPtr;

 char *getWord(FILE *fp);
 void removeNewline(char *str);
 int isValidWord(char *str);
 trieNodePtr makeNode(void);
 void insertWord(trieNodePtr root, char *string);
 boardPtr makeBoard(int NROWS, int NCOLS, char *letters);
 void traverseUtil(boardPtr board, trieNodePtr trie, int row, int col, int seen[], int noReuse);
 void traverse(boardPtr board, trieNodePtr trie, int noReuse);
 void printWords(trieNodePtr trie, int showNonBoggleWords);

 #endif
 /* end BOGGLE_H */
