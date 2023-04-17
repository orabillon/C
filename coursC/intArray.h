#ifndef __INT_ARRAY_h__
#define __INT_ARRAY_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct intarray
{
    int *data;
    int len;

} intarray;

intarray intArray_create(int len);

void intArray_debug(intarray array);
void intArray_positive_values(intarray array);
bool intArray_search(intarray array, int n);
int intArray_nb_occurences(intarray array, int n);

#endif