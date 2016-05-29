/******************************************************************************
 * Queue.c
 * Implementation of Queue ADT
 *
 * HWK #4
 * Merging Queues
 *
 * Harrison Miller
 ******************************************************************************/

#include <stdlib.h> 
#include "/c/cs223/Hwk4/Queue.h"

typedef struct node {
   int data;
   struct node* next;
 } Node;

 // Set *Q to a new object of type Queue.  Return status.

int createQ (Queue *q) {
    if(!(q = malloc(sizeof(node)))) {
        return false;
    }

    q->data = NULL;
    q->next = q;

    return true;
}


// Add the string pointer S to the tail of Queue *Q; the string itself is not
// copied.  *Q may change as a result.  Return status.

int addQ (Queue *q, char *s) {
    Node *new;

    if(!q || !s) {
        return false;
    }

    new->data = s;

    if(isEmptyQ(q)) {
        q = new;
        q->next = q;
    } else {
        new->next = q;
        q = new;
    }

    return true;
}


// Return TRUE if the Queue *Q is empty, FALSE otherwise.  *Q may change as a
// result.

int isEmptyQ (Queue *q) {
    return !q;     
}

// Copy the string pointer at the head of Queue *Q to *S, but do not remove it
// from *Q.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int headQ (Queue *q, char **s) {

    if(isEmptyQ(q)) {
        return false;
    }

    return true;
}


// Remove the string pointer at the head of the Queue *Q and store that value
// in *S.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int removeQ (Queue *q, char **s) {
    return true;
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
    return true;
}



