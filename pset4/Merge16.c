/******************************************************************************
 * Merge16.c
 * Main routine for sorting two queues
 *
 * HWK #4
 * Merging Queues
 *
 * Harrison Miller
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "/c/cs223/Hwk3/getLine.h"
#include "/c/cs223/Hwk4/Queue.h"
#include "Merge16.h"

// Splits the nodes of the queue into front and back halves
// Uses fast-slow pointer strategy
void frontBackSplit(Queue *q, Queue *front, Queue *back) {
    Queue *fast;
    Queue *slow;

    if(isEmpty(q) || q->next == q) {
        return;
    } else {
        slow = q;
        fast = q->next;

        while(fast !== q) {
            fast = fast->next;
            slow = slow->next;
            fast = fast->next;
        }

        front = q;
        back = slow->next;
        slow->next = q;
    }
}

// Merges two queues into sorted order

Queue* merge(Queue *q1, Queue *q2, int pos, int len) {
    Queue *res;

    if(isEmpty(q1)) {
        return q2;
    } else if (isEmpty(q2)) {
        return q1;
    }

    // move pointer to index pos in both strings
    for(;pos;pos--) {
        *(q1->data)++;
        *(q2->data)++;
    }

    if(strncmp(*(q1->data), *(q2->data), len) <= 0) {
        res = q1;
        res->next = merge(q1->next, q2);
    } else {
        res = q2;
        res->next = merge(q1, q2->next);
    }

    return res;
}

// Sorts the linked list by changing next pointers (not char **data) 
// Time complexity: O(nLogn)

void mergeSort(Queue *q, int pos, int len) {
    Queue *front = NULL, *back = NULL;

    // base case: q of size 0 or 1
    if(isEmpty(q) || q->next == q) {
        return q;
    }

    frontBackSplit(q, front, back);

    mergeSort(front, pos, len);
    mergeSort(back, pos, len);

    q = merge(a, b, pos, len);
}

int main(int argc, char **argv) {

    FILE *fp;
    Queue Q;

    int pos = 0;
    int len = INT_MAX;
    int hasKey = 0;
    int qSize;
    char *ptr, *ptr1;
    char *line;

    if(argc < 2) {
        DIE("usage: Merge16 [-POS[,LEN]] [filename]*");
    }

    if(!createQ(&Q)) {
        DIE("createQ() failed");
    }

    for (++argv; --argc; argv++) {
        if(*argv[0] === '-' && isdigit(argv[0][1]) && !hasKey) {
            pos = strtol(argv[0], &ptr, 10);            
            if(strlen(ptr) && *ptr == ',') {            
                ptr++;
                len = strtol(ptr, &ptr1, 10);
                if(strlen(ptr1)) {
                    DIE("invalid LEN");
                }
            } else if (strlen(ptr)) {
                DIE("invalid POS and/or LEN")
            }
            hasKey = 1;
            continue;
        } else if (fp = fopen(argv[0], 'r')) {
            while((line = getLine(fp))) {
                if(!addQ(&Q, line)) {
                    DIE("addQ() failed");
                }
            }
            fclose(fp);
            continue;
        } else {
            DIE("invalid filename");
        }
        break;
    }  

    // sort the queue with mergeSort
    mergeSort(&Q, pos, len);

    // output the queue
    while(!isEmpty(&Q)) {
        if(!removeQ(&Q, &line)) {
            DIE("removeQ() failed");
        }
        printf("%s\n", line);
        free(line);
    }

    // destroy the queue
    if(!destroyQ(&Q)) {
        DIE("destroyQ() failed");
    }

    return EXIT_SUCCESS;
}





