/******************************************************************************
 * Queue.c
 * Implementation of Queue ADT
 *
 * HWK #4
 * Merging Queues
 *
 * Harrison Miller
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include "/c/cs223/Hwk4/Queue.h"

typedef struct node {
   int data;
   struct node* next;
 } node;

 // Set *Q to a new object of type Queue.  Return status.

int createQ (Queue *q) {
    if(!(q = malloc(sizeof(Queue)))) {
        return 0;
    }

    q->data = NULL;
    q->next = NULL;

    return 1;
}


// Add the string pointer S to the tail of Queue *Q; the string itself is not
// copied.  *Q may change as a result.  Return status.

int addQ (Queue *q, char *s) {
    if(!q || !s) {
        return 0;
    }



}


// Return TRUE if the Queue *Q is empty, FALSE otherwise.  *Q may change as a
// result.

int isEmptyQ (Queue *q) {

}

// Copy the string pointer at the head of Queue *Q to *S, but do not remove it
// from *Q.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int headQ (Queue *q, char **s) {

}


// Remove the string pointer at the head of the Queue *Q and store that value
// in *S.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int removeQ (Queue *q, char **s) {

}


// Destroy the Queue *Q by freeing any storage it uses (but not that to which
// the string pointers point).  Set *Q to NULL.  Return status.

int destroyQ (Queue *q) {
    node *doomed;
    char **s;

    while(!isEmpty(q)) {
        doomed = removeQ(q, s);
        free(doomed);
    }
    
    free(q);
}



