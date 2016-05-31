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

#define ADDQ(Q,S) if(!addQ(Q,S)) DIE("addQ() failed");
#define CREATEQ(Q) if(!createQ(Q)) DIE("createQ() failed");
#define HEADQ(Q) if(!headQ(Q, S)) DIE("headQ() failed");
#define ISEMPTYQ(Q) return isEmptyQ(Q)
#define REMOVEQ(Q,S) if(!removeQ(Q,S)) DIE("removeQ() failed");
#define DESTROYQ(Q) if(!destroyQ(Q))) DIE("destroyQ() failed"); 

void removeNewline(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

// Custom strcmp that compares keys
int Strcmp(const char *s1, const char *s2, int pos, int len) {
if(pos > strlen(s1)) {
 s1 = &s1[strlen(s1)];
} else {
 s1 = s1+pos;
}

if(pos > strlen(s2)) {
 s2 = &s2[strlen(s2)]
} else {
 s2 = s2+pos;
}

return strncmp(s1, s2, len);
}

int main(int argc, char **argv) {

    FILE *fp;
    Queue Q1, Q2;
    int times = 2;
    int res;
    int q1Count = 0, q2Count = 0;
    int pos = 0;
    int len = INT_MAX;
    int hasKey = 0;
    char *ptr, *ptr1;
    char *line, *nextLine;

    if(argc < 2) {
        DIE("usage: Merge16 [-POS[,LEN]] [filename]*");
    }


    // create the 2 queues
    CREATEQ(&Q1);
    CREATEQ(&Q2);

    Queue *activeQ = &Q1;

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

        } else if ((fp = fopen(argv[0], 'r'))) {

            while((line = getLine(fp))) {
                  removeNewline(line);

                  if((nextLine = getLine(fp))) {
                    removeNewline(nextLine);
                    res = Strcmp(line, nextLine, pos, len);

			  if(res <= 0) {
			    ADDQ(activeQ, line);
			    ADDQ(activeQ, nextLine);
			  } else {
			    ADDQ(activeQ, nextLine);
			    ADDQ(activeQ, line);
			  } 

                  } else {
                    ADDQ(activeQ, line);

                    if(q == &Q1) q1Count++;
                    else q2Count++;

		    break;
                  }

                 
                  if(activeQ == &Q1) {
		    q1Count += 2;
                    activeQ = &Q2;
                  } else if (activeQ == &Q2) {
		    q2Count += 2;
		    activeQ = &Q1;
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
    int *activeQ = &Q1;
    char *s1, *s2, *next;
    int bSize1, bSize2;

    while(count > bSize) {
        // Merge process right here
        for(int b=0; b<(count+1)/bSize; b++) {
            for(int p = 0; p < bSize*2 ; p++) {
		bSize1 = bSize2 = bSize;

		HEADQ(&Q1, &s1);
		HEADQ(&Q2, &s2);

		if(s1 && s2 && bSize1 && Strcmp(s1, s2, pos, len) <= 0) {
		 REMOVEQ(&Q1, s1);
		 ADDQ(activeQ, s1);

		 q1Count--;
		 activeQ == &Q1 ? q1Count++ : q2Count++;
		 bSize1--;
 		} else if(s1 && s2 && bSize2 && Strcmp(s1,s2,pos,len) > 0){
		 REMOVEQ(&Q2, s2);
		 ADDQ(activeQ, s2);

	         q2Count--;
		 activeQ == &Q1 ? q1Count++ : q2Count++;
		 bSize2--;
		} else if (s1 && bSize1) {
		 REMOVEQ(&Q1, s1);
  		 ADDQ(activeQ, s1);

		 q1Count--;
		 activeQ == &Q1 ? q1Count++ : q2Count++;
		 bSize1--;
		} else if (s2 && bSize2) {
		 REMOVEQ(&Q2, s2);
		 ADDQ(activeQ, s2);

		 q2Count--;
		 activeQ == &Q1 ? q1Count++ : q2Count++;
		 bSize2--;
		} else {
		  break;
		}
			
		// iterate over the length of the combined bucke
		// have to make sure you don't add more than bSize elements
		// from one q (even if they are < elements in the other queue
            }

            // Switch queues
            // // maybe update the lengths of each q based on how many remove
            // and how many added
            if(activeQ == &Q1) {
                activeQ = &Q2;
            } else if (activeQ == &Q2) {
                activeQ = &Q1;
            }
		// keep track of number of entries read from each queue,
		// dont remove more when numremoved = bSize
        }
	count = q1Count > q2Count ? q1Count : q2Count;
        bSize *= 2;
    }


    // Print queue
    // output the queue
    while(!ISEMPTYQ(&Q1) || !ISEMPTY(&Q2)) {
        REMOVEQ(&Q1, &line);
	REMOVEQ(&Q2, &nextLine);
	
	if(line && nextLine && Strcmp(line, nextLine, pos, len) <= 0) { 
        printf("%s\n", line);
        printf("%s\n", nextLine);
	} else if (line && nextLine && Strcmp(line, nextLine, pos, len > 0) {
        printf("%s\n", nextLine);
        printf("%s\n", line);
	} else if (line) {
        printf("%s\n", line);
	}  else if (nextLine) {
        printf("%s\n", nextLine);
	} else {
	 break;
	}

        if(line) free(line);
	if(nextLine) free(nextLine);
    }

    // destroy the 2 queues
    DESTROYQ(&Q1);
    DESTROYQ(&Q2);

    return EXIT_SUCCESS;
}





