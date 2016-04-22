#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "part1.h"

/*
 * Implement the C function called part1_opt. It should perform
 * the same task as the implemented part1 function. In the
 * comments for the function describe why your changes make the
 * function more cache friendly.
*/

int part1(int* B, int x, int y)
{
    if (!B) return -1;

    int c, r;
    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            B[r * N + c] = 2 * (B[r * N + c] + 2);

    return B[x * N + y];
}

/*
 * Interchanging the loops provide a stride-1 reference pattern,
 * thereby reducing cache misses. In part1, spacial locality of 
 * data in and reference of array B is not utililized: traversal 
 * through array B is not done by accessing/referencing succesive  
 * elements because of which cache misses increase.
*/
int part1_opt(int* B, int x, int y)
{
    if (!B) return -1;

    int c, r;
    for(r = 0; r < N; r++)
        for(c = 0; c < N; c++)
            B[r * N + c] = 2 * (B[r * N + c] + 2);

    return B[x * N + y];
}
