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
    if(!(q = malloc(sizeof(Node)))) {
        return false;
    }

    q->data = NULL;                             // initialize data
    q->next = q;                                // make head point to itself

    return true;
}


// Add the string pointer S to the tail of Queue *Q; the string itself is not
// copied.  *Q may change as a result.  Return status.

int addQ (Queue *q, char *s) {
    Node *new, *tmp;

    if(!s) {
        return false;
    }

    if(!(new = malloc(sizeof(Node)))) {
        return false;
    }

    tmp = q;
    new->data = &s;

    if(isEmptyQ(q)) {                           // if queue is empty
        q = new;                                // set q to new node
        q->next = q;                            // make it point to itself
    } else {
        while(tmp && tmp->next != q) {          // traverse to tail
            tmp = tmp->next;
        }
        tmp->next = new;                        // append new node to tail       
        new->next = q;                          // new tail points to head
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

    **s = (*q)->data;

    return true;
}


// Remove the string pointer at the head of the Queue *Q and store that value
// in *S.  *Q may change as a result.  Return status.  (If *Q is empty, then
// returns FALSE and leaves *S unchanged.)

int removeQ (Queue *q, char **s) {
    Node *tmp;

    if(isEmptyQ(q)) {
        return false;
    }

    if(s) {
        **s = (*q)->data;                                 // store string pointer
    }

    q->data = q->next = NULL;

    tmp = q;

    while(tmp && tmp->next != q) {                      // traverse to tail
        tmp = tmp->next;
    }

    tmp->next = q->next;     
    q = q->next;                          

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

    *q = NULL;
    free(q);
    
    return true;
}



