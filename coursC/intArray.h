#ifndef __INT_ARRAY_h__
#define __INT_ARRAY_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void intArray_debug(int *tab, int len);
void intArray_positive_values(int *tab, int len);

bool intArray_search(int *tab, int len, int n);
int intArray_nb_occurences(int *tab, int len, int n);

#endif