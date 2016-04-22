#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "part3.h"

/*
 * Implement the C function called part3_opt. It should perform
 * the same task as the implemented part3 function. In the
 * comments for the function describe why your changes make the
 * function more cache friendly.
 *
 * You may observe that this function performs "useless" looping
 * over an array of structures that are all filled with zero bits.
 * Your task is not to remove that "useless" code, but modify it
 * so that it is more cache friendly. You also should not be removing
 * any parts of the structures.
 */

char* part3()
{
    // Note: struct 'data' is defined in part3.h, take a look
    data* B = (data*) calloc(LARGER, sizeof(data));
    if (!B) return 0;

    double sum_f = 0.0;
    double sum_n = 0;
    char* sum_c = (char*) malloc(( 2 * LARGER + 1) * sizeof(char));

    sum_c[2 * LARGER] = '\0';

    int i;
    for(i = 0; i < LARGER; i++)
    {
        sum_f += B[i].f1 + B[i].f2;
        sum_n += B[i].n1 + B[i].n2;
        sum_c[2 * i] = B[i].c1;
        sum_c[2 * i + 1] = B[i].c2;
    }

    free(B);
    return sum_c;
}

/*
 * The only difference between the two functions is their definitions
 * of the struct. In part3, the struct is not packed, and the order
 * of the elements in it is such that more space is being used in the heap
 * to store a struct. Also the order of elements in it doesn't match the 
 * order in which it is accessed in the code. Packing the struct reduces space 
 * to store it on the heap and provides right order in which it is accessed
 * in the code -> first avoiding capacity miss and latter improving spacial 
 * locality -> better cache performance.
*/
char* part3_opt()
{

    data1* B = (data1*) calloc(LARGER, sizeof(data));
    if (!B) return 0;

    // DO NOT modify the following 4 lines
    double sum_f = 0.0;
    double sum_n = 0;
    char* sum_c = (char*) malloc((2 * LARGER + 1) * sizeof(char));
    sum_c[2 * LARGER] = '\0';
    // DO NOT modify the preceeding 4 lines

    int i;
    for(i = 0; i < LARGER ; i++)
    {
        sum_f += B[i].f1 + B[i].f2;
        sum_n += B[i].n1 + B[i].n2;
        sum_c[2 * i] = B[i].c1;
        sum_c[2 * i + 1] = B[i].c2;
        
    }
    
    free(B);
    return sum_c;
}
