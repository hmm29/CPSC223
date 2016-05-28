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
#include "/c/cs223/Hwk4/Queue.h"
#include "Merge16.h"

// Print message to stderr and exit.
#define DIE(msg) exit (fprintf (stderr, "%s\n", msg));

int pos = 0;
int len = 0;

char *getLine(FILE *fp)
{
    char *line;                 // Line being read
    int size;                   // #chars allocated
    int c, i;

    size = sizeof(double);                      // Minimum allocation
    line = malloc (size);
    for (i = 0;  (c = getc(fp)) != EOF; )  {
	if (i == size-1) {
	    size *= 2;                          // Double allocation
	    line = realloc (line, size);
	}
	line[i++] = c;
	if (c == '\n')                          // Break on newline
	    break;
    }

    if (c == EOF && i == 0)  {                  // Check for immediate EOF
	free (line);
	return NULL;
    }

    line[i++] = '\0';                           // Terminate line
    line = realloc (line, i);                   // Trim excess storage

    return (line);
}

int main(int argc, char **argv) {
  const char s[2] = ",";

  if (argc < 3) {
    DIE("usage: Merge16 [-POS[,LEN]] [filename]*");
  }

    // argument parsing
    for (int i = 1; i < argc; i++) {
        if(i == 1) {
            if(*argv[i] != '-') { // no '-'
                DIE("invalid [-POS[,LEN]]");
            } else if (strlen(argv[i]) == 1) { // only '-'
                pos = NULL;
                len = INT_MAX;
            } else if (strcspn(argv[i], s) == strlen(argv[i])) { // if no comma
                pos = atoi();
            } else if (strcspn(argv[i], s) < strlen(argv[i])-1 && strcspn(argv[i], s) > 1) { // if comma in middle of string
              pos = atoi(strtok(argv[1], s));
              len = atoi(strtok(NULL, s));
            } else {
              DIE("invalid [-POS[,LEN]]");
            }
        }

        if(i > 1) {
           File *fp;
        }
    }

    FILE *fp = stdin;           // Read from standard input */
    Queue Q;
    char *line;

    if (!createQ (&Q))                          // Create Queue for stdin
        DIE ("createQ() failed");

    while ((line = getLine(fp))) {              // Append lines read to Q
        if (!addQ (&Q, line))
            DIE ("addQ() failed");
    }

    while (!isEmptyQ (&Q)) {                    // Output lines in Q
        if (!removeQ (&Q, &line))
            DIE ("removeQ() failed");
        fputs (line, stdout);
        free (line);                            // Free storage for line
    }

    if (!destroyQ (&Q))                         // Destroy Queue
        DIE ("destroyQ() failed");

    return EXIT_SUCCESS;
}


