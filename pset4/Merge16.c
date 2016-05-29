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

int countQ(Queue *q) {
    Node *tmp;
    int count = 1;

    if(isEmptyQ(q)) return 0;

    for(tmp = q; tmp && tmp->next != q; tmp = tmp->next) {
        count++;
    }

    return count;
}

void merge(Queue *q, int l, int m, int r, int pos, int len) {
    int i, j, k;
    int n1 = m-1+1;
    int n2 = r-m;
    Queue q1, q2;

    
}

void mergeSort(Queue *q, int l, int r, int pos, int len) {
    int mid;

    if(l < r) {
        mid = l+(r-1)/2;                // get idx of middle elt
        mergeSort(q, l, mid);           // sort left subqueue
        mergeSort(q, mid+1, r);         // sort right subqueue
        merge(q, l, mid, r);            // merge subqueues
    }
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
    qSize = countQ(&Q);
    mergeSort(&Q, 0, --qSize, pos, len);

    // output the Q
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





