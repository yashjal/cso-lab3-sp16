#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "part5.h"

/*
 * Implement the C function called part5_opt. It should perform
 * the same task as the implemented part5 function. In the
 * comments for the function describe why your changes make the
 * function more cache friendly.
 *
 * Note: Data structures like linked lists are not very
 * cache friendly (their nodes can be scattered all over
 * the heap). The following method packs the nodes of a linked 
 * list into adjacent memory locations in an array and it also
 * preserves the traditional linked list connections. 
 * Your own code needs to accomplish the same. 
 */

void part5(node** head, int length)
{
    // Malloc a contiguous block of memory on the heap
    // that is big enough for the entire list.
    node* new_list = malloc(sizeof(node) * length);

    // Go through the list and make a copy of all the 
    // nodes and place them into the contiguous block in order
    node* n = *head;
    int i;
    for(i = 0 ; i < length ; ++i) {
        node copy = { n->value, NULL };
        new_list[i] = copy;
        n = n->next;
    }

    // Go through the list again and "link" each node in 
    // the contiguous block to the next node in memory; 
    // free all the nodes in the old list
    n = *head;
    for(i = 0 ; i < length - 1 ; ++i) {
        // Link each node in the new list
        new_list[i].next = &new_list[i+1];
        // Free the old nodes
        node* free_me = n;
        n = n->next;
        free(free_me);
    }

    // Free the last node of the old list
    free(n);

    // Point head at the new packed list
    *head = new_list;

    return;
}

/*
 * The only difference between the two functions is that instead
 * of "Go(ing) through the list again and "link(ing)" each node...",
 * this function only goes through the list once and while copying
 * the nodes into place, it links the 2 nodes and frees it too.
 * By doing this, the old linked list is only traversed once, not twice.
 * Traversing the old list, which does not exhibit any spacial locality, once 
 * reduces the number of times the old list nodes are accessed and referenced ,
 * thus reducing cache writes and reads.
*/
void part5_opt(node** head, int length)
{
     // Malloc a contiguous block of memory on the heap
    // that is big enough for the entire list.
    node* new_list = malloc(sizeof(node) * length);

    // Go through the list and make a copy of all the 
    // nodes and place them into the contiguous block in order
    node* n = *head;
    int i;
    for(i = 0 ; i < length ; ++i) {
        node copy = { n->value, n->next };
        new_list[i] = copy;
        node* free_me = n;
        n = n->next;
        free(free_me);
    }

    // Free the last node of the old list
    free(n);

    // Point head at the new packed list
    *head = new_list;

    return;
}
