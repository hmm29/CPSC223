/*
 * File: boggle.h
 * Programmer: Harrison Miller
 * Description: this file contains typedef declarations and function prototypes
 * for the functions defined and called in boggle.c.
 */

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
   int count;
 } trieNode;

 typedef struct trieNode *trieNodePtr;

 typedef struct board {
   int NROWS;
   int NCOLS;
   char grid[MAX_BOARD_LENGTH][MAX_BOARD_LENGTH];
 } board;

 typedef struct board *boardPtr;

 char *getWord(FILE *fp);
 void removeNewline(char *str);
 int isValidWord(char *str);
 trieNodePtr makeNode(void);
 void insertWord(trieNodePtr root, char *string);
 boardPtr makeBoard(int NROWS, int NCOLS, char *letters);
 void traverseUtil(boardPtr board, trieNodePtr t, int row, int col, int seen[], char* word, int noReuse);
 void traverse(boardPtr board, trieNodePtr trie, int noReuse);
 void printWords(trieNodePtr trie, int showNonBoggleWords);
 void clearTrie(trieNodePtr root);

 #endif
 /* end BOGGLE_H */
