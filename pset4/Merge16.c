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

void removeNewline(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

// Custom strcmp that compares keys
int Strcmp(char *s1, char *s2, int pos, int len) {

}

int main(int argc, char **argv) {

    FILE *fp;
    Queue Q1, Q2;

    int times = 2;
    int res;
    int q1Count = 0; q2Count = 0;
    int pos = 0;
    int len = INT_MAX;
    int hasKey = 0;
    char *ptr, *ptr1;
    char *line, *nextLine;

    if(argc < 2) {
        DIE("usage: Merge16 [-POS[,LEN]] [filename]*");
    }

    if(!createQ(&Q1) || !createQ(&Q2)) {
        DIE("createQ() failed");
    }

    Queue *q = &Q1;

    // arg parsing
    for (++argv; --argc; argv++) {
        if(*argv[0] == '-' && isdigit(argv[0][1]) && !hasKey) {
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
                  removeNewline(line);

                  if(nextLine = getLine(fp)) {
                    removeNewline(nextLine);
                    res = Strcmp(line, nextLine, pos, len);
                  } else {
                    addQ(q, line);

                    if(q == &Q1) q1Count++;
                    else q2Count++;
                  }

                  if(res <= 0) {
                    addQ(q, line);
                    addQ(q, nextLine);
                    q1Count++;
                    q2Count++;
                  } else {
                    addQ(q, nextLine);
                    addQ(q, line);
                    q1Count++;
                    q2Count++;
                  }
                  
                  if(q == &Q1) {
                    q = &Q2;
                  } else if (q == &Q2) {
                    q = &Q1;
                  }
            }

            fclose(fp);
            continue;
        } else {
            DIE("invalid filename");
        }
        break;
    }  


    int count = q1Count > q2Count ? q1Count : q2Count;
    int bSize = 2;

    while(count != bSize) {
        // Merge process right here
        for(int b=0; b<=count/bSize && count != bSize; b++) {
            for(int p = 0; p < bSize; p++) {
                if(headQ(&Q1, s1) && headQ(&Q2, s2)) {
                    if(Strcmp(s1, s2, pos, len) <= 0) {
                        removeQ(&Q1, s1);
                        addQ(q, s1);
                        removeQ(&Q2, s2);
                        addQ(q, s2);
                    } else {
                        removeQ(&Q2, s2);
                        addQ(q, s2);
                        removeQ(&Q1, s1);
                        addQ(q, s1);
                    }

                } else if (headQ(&Q1, s1)) {
                    removeQ(&Q1, s1);
                    addQ(q, s1);
                } else if (headQ(&Q2, s2)) {
                    removeQ(&Q2, s2);
                    addQ(q, s2);
                } else {
                    break;
                }
            }

            // Switch queues
            if(q == &Q1) {
                q = &Q2;
            } else if (q == &Q2) {
                q = &Q1;
            }

        }

        count = 
        bSize *= 2;
    }


    // Print queue
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





