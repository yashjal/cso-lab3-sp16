#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "part2.h"

/*
 * Implement the C function called part2_opt. It should perform
 * the same task as the implemented part2 function. In the
 * comments for the function describe why your changes make the
 * function more cache friendly.
 *
 * Note: Your function needs to compute the entire matrix A, not only A[x+y]
 */

double part2(double* B, double* A, int x, int y)
{
    int i, j;
    for(i = 0; i < LARGE; i++)
        for(j = 0; j < SMALL; j++)
            A[i] = A[i] + B[ j * LARGE + i];

    return A[x+y];
}

/*
 * In part2, spacial locality of accessing data from array B
 * is not utilized. By interchanging the loops, spacial locality
 * of referencing/accessing data A is preserved by adding temperal
 * locality and also accessing data from B is achieved with a stride-1 
 * reference pattern; thus reducing cache misses.
*/

double part2_opt(double * B, double * A, int x, int y )
{
    int i, j;
    for(j = 0; j < SMALL; j++)
        for(i = 0; i < LARGE; i++)
            A[i] = A[i] + B[ j * LARGE + i];
    
    return A[x+y];
}
