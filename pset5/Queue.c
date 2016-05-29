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
   char **data;
   struct node *next;
 } Node;

 // Set *Q to a new object of type Queue.  Return status.

int createQ (Queue *q) {
    // queue already exists
    if(!isEmptyQ(q)) {
        return false;
    }

    if(!(q = malloc(sizeof(Queue)))) {
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

    if(!s) {
        return false;
    }

    if(isEmptyQ(q)) {
        createQ(q);
        q->data = &s;
        return true;
    }

    if(!(new = malloc(sizeof(Node)))) {
        return false;
    }

    new->data = &s;
    new->next = q->next;
    q->next = new;                                      
    q = new;                                              
    
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
    s = q->next->data;
    return true;
}


// Remove the string pointer at the head of the Queue *Q and store that value
// in *S.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int removeQ (Queue *q, char **s) {
    if(isEmptyQ(q)) {
        return false;
    }

    if(s) {
        s = q->next->data;                            // store head string ptr
    }

    q->next->data = NULL;
    q->next = q->next->next;
    free(q->next);                     

    return true;
}


// Destroy the Queue *Q by freeing any storage it uses (but not that to which
// the string pointers point).  Set *Q to NULL.  Return status.

int destroyQ (Queue *q) {
    while(!isEmpty(q)) {
        if(!removeQ(q, NULL)) {
            return false;
        }
    }

    q = NULL;
    return true;
}



