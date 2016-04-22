#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "part4.h"

/*
 * Implement the C function called part4_opt. It should perform
 * the same task as the implemented part4 function. In the
 * comments for the function describe why your changes make the
 * function more cache friendly.
 * 
 * Note: your function needs to compute the entire matrix C, not only C[x]. 
 */

long part4(long* B, long* A, int x) {
    long* C = (long*) calloc(N, sizeof(long));
    if (!C) return 0; 

    int c, r; 
    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            C[r] = B[r * N + c] + A[c * N + r];
    
    long ret = C[x];
    free(C); 
    return ret;
}

/*
 * Instead of traversing and accessing elements of array B without
 * exploiting spacial locality, this function creates two temp arrays,
 * and fills it with appropriate values from arrays A and B, so that C[i] = A[i] + B[i].
 * While filling the two temp arrays, the function exploits spacial 
 * locality of A and B and accesses only successive elements from A and B,
 * thus achieving a stride-1 reference pattern for both arrays -> improving
 * cache performance.
*/
long part4_opt(long* B, long* A, int x) {
    long* C = (long*) calloc(N, sizeof(long));
    if (!C) return 0;
    long* Atmp = (long*) calloc(N, sizeof(long));
    if (!Atmp) return 0;
    long* Btmp = (long*) calloc(N, sizeof(long));
    if (!Btmp) return 0;

    int c, r, i;

    for(c = 0; c < N; c++) {
        for(r = 0; r < N; r++) {
            Atmp[r] = A[c * N + r];
            Btmp[c] = B[c * N + r];
        }
    }

    for (i = 0; i < N; i++)
        C[i] = Atmp[i] + Btmp[i];
    
    long ret = C[x];
    free(C);
    free(Btmp);
    free(Atmp);
    return ret;
}
