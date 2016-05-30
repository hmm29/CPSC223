/******************************************************************************
 * Merge16.c
 * Main routine for sorting two queues
 *
 * HWK #5
 * Pancake Sort
 *
 * Harrison Miller
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "/c/cs223/Hwk3/getLine.h"
#include "/c/cs223/Hwk4/Queue.h"
#include "Pancake.h"

 void flip(Queue *q, int i) {
    int tmp;

    while(start < i) {
        tmp = 
    }
 }

int getMax(Queue *q, int n) {
    int max = 0;
    Node *tmp = q;

    do {
       if(tmp->data > max) max = tmp->data; 
       tmp = tmp->next;
    } while(tmp && tmp != q)

    return max;
}

int pancakeSort(Queue *q, int n) {
    for(int currSize = n; currSize > 1; currSize--) {
        int max = getMax(q, currSize);

        if(max == currSize-1) {
            flip(q, max);

            flip(q, currSize-1);
        }
    }
}

int main(int argc, char **argv) {

    Queue Q;
    char *INITIAL, *GOAL;

    if(argc < 4) {
        DIE("pancake [HEIGHT WIDTH] MAXLENGTH INITIAL GOAL");
    }

    // parse arguments one at a time
    for (++argv; --argc; argv++) {
        
        break;
    }  

    // sort the queue with mergeSort
    pancakeSort(&Q, INITIAL, GOAL);

    return EXIT_SUCCESS;
}





