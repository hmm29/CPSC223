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
   struct node *children[ALPHABET_SIZE];
   int isTerminal;
   int used;
   int count;
 } trieNode;

 typedef struct trieNode *trieNodePtr;

 typedef struct board {
   int NROWS;
   int NCOLS;
   char grid[MAX_BOARD_LENGTH][MAX_BOARD_LENGTH];
 } board;

 typedef struct board *boardPtr;

 int getWord(File fp);
 trieNodePtr makeNode(void);
 void insertWord(trieNodePtr root, char *string);
 void traverse(boardPtr board, trieNodePtr t, int row, int col);
 void printWords(trieNodePtr t);
 void clearTrie (trieNodePtr root);
 boardPtr makeBoard(int NROWS, int NCOLS, char *letters) {

 #endif
 /* end BOGGLE_H */
