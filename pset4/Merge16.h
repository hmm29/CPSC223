/******************************************************************************
 * Merge16.h
 * This file contains typedef declarations and function prototypes
 * for the functions defined and called in Merge16.c.
 *
 * Harrison Miller
 ******************************************************************************/

 #ifndef MERGE16_H
 #define MERGE16_H

// Print message to stderr and exit.
#define DIE(msg) exit (fprintf (stderr, "%s\n", msg));

 // function prototypes
 void merge(Queue *q, int l, int m, int r);
 void mergeSort(Queue *q, int l, int r);

 #endif
 /* end MERGE16_H */