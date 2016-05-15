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
 #include <stdbool.h>

 #define ALPHABET_SIZE 26
 #define MAX_BOARD_DIMENSION 10
 #define MAX_NUM_WORDS 100

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
   char grid[MAX_BOARD_DIMENSION][MAX_BOARD_DIMENSION];
 } board;

 typedef struct board *boardPtr;

 void initializeNode(trieNodePtr t);
 void insert(trieNodePtr root, char *string);
 int trieNodeHasChildren(trieNodePtr t);
 int search(trieNodePtr root, char *string);
 void removeNewline(char *s);
 int isValidWord(char *s);
 boardPtr createBoard(int NROWS, int NCOLS, char *string);
 void checkBoard(boardPtr board, trieNodePtr t, int row, int col, int seen[], char* word);
 void checkPath(BoardPtr board, TrieNodePtr trie, int row, int col);
 void traverseBoard(BoardPtr board, TrieNodePtr trie);
 int clearTrie (trieNodePtr root);

 #endif
 /* end BOGGLE_H */
