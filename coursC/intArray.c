#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intArray.h"

void intArray_debug(intarray array)
{
    printf("[ ");
    for (int i = 0; i < array.len - 1; i++)
    {
        printf("%d, ", array.data[i]);
    }
    printf("%d ", array.data[array.len - 1]);
    printf(" ]");
}

void intArray_positive_values(intarray array)
{
    printf("[ ");
    for (int i = 0; i < array.len; i++)
    {
        if (array.data[i] >= 0)
            printf(" %d ", array.data[i]);
    }
    printf(" ]");
}

bool intArray_search(intarray array, int n)
{
    for (int i = 0; i < array.len; i++)
    {
        if (array.data[i] == n)
        {
            return true;
        }
    }

    return false;
}

int intArray_nb_occurences(intarray array, int n)
{
    int occur = 0;

    for (int i = 0; i < array.len; i++)
    {
        if (array.data[i] == n)
        {
            occur++;
        }
    }

    return occur;
}

intarray intArray_create(int len)
{
    intarray array;
    array.len = len;
    array.data = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        array.data[i] = 0;
    }
    return array;
}

// --------------------------------------------------------------------- TEST MDULE --------------------------------------------------------------------------------

int main()
{

    intarray array = intArray_create(8);

    for (int i = 0; i < array.len; i++)
    {
        array.data[i] = 6 * i + 4;
    }

    array.data[1] = -20;
    array.data[4] = 20;
    array.data[6] = -20;

    intArray_positive_values(array);

    free(array.data);

    return EXIT_SUCCESS;
}