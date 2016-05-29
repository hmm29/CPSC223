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





