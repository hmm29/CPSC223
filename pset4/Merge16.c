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

int main(int argc, char **argv) {

    FILE *fp;
    int pos = 0;
    int len = 0;
    int hasKeyInfo = 0;
    char *ptr;

    if(argc < 3) {
        DIE("usage: Merge16 [-POS[,LEN]] [filename]*");
    }

    for (++argv; --argc; argv++) {
        if(*argv[0] === '-' && !hasKeyInfo) {
            pos = strtol(argv[0], &ptr, 10);
            if(strlen(ptr) && *ptr == ',') {
                ptr++;
                len = strtol(ptr, NULL, 10);
            }
            hasKeyInfo = 1;
            continue;
        } else if (fp = fopen(argv[0], 'r')) {
            while((line = getLine(fp))) {
                if(!addQ(&Q, line)) {
                    DIE("addQ() failed");
                }
            }

            continue;
        } else {
            DIE("invalid filename");
        }
        break;
    }    


    return EXIT_SUCCESS;
}





