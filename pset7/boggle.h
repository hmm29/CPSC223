/*
 * File: boggle.h
 * Programmer: Harrison Miller
 * Description: this file contains function prototypes for the functions defined and called in boggle.c.
 */

 #ifndef BOGGLE_H
 #define BOGGLE_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <string.h>
 #include <stdbool.h>

 typedef struct trieNode {
   struct node *children[ALPHABET_SIZE];
   bool isTerminal;
   bool used;
 } trieNode;

 typedef struct trieNode *trieNodePtr;

 typedef struct board {
   int NROWS;
   int NCOLS;
   int size;
   char grid[NROWS][NCOLS];
 } board;

 typedef struct board *boardPtr;

 void initializeNode(trieNodePtr t);
 void insert(trieNodePtr root, char *string);
 int trieNodeHasChildren(trieNodePtr t);
 int search(trieNodePtr root, char *string);

 #endif
 /* end BOGGLE_H */
