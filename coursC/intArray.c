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

void intArray_destroy(intarray array)
{
    free(array.data);
}

int intArray_get(intarray array, int index)
{
    if ((index < 0) || (index >= array.len))
    {
        printf("intArray_get : L'index %d est invalide.\n les valeurs valide sont entre %d et %d.\n", index, 0, array.len - 1);
        return -1;
    }

    return array.data[index];
}

void intArray_set(intarray array, int index, int value)
{
    if ((index < 0) || (index >= array.len))
    {
        printf("intArray_set : L'index %d est invalide.\n les valeurs valide sont entre %d et %d.\n", index, 0, array.len - 1);
        return;
    }

    array.data[index] = value;
}

int intArray_length(intarray array)
{
    return array.len;
}

// --------------------------------------------------------------------- TEST MDULE --------------------------------------------------------------------------------

int main()
{

    intarray array = intArray_create(8);

    for (int i = 0; i < array.len; i++)
    {
        array.data[i] = 6 * i + 4;
    }

    intArray_set(array, 5, 13);

    intArray_debug(array);
    printf("\n");

    intArray_destroy(array);

    return EXIT_SUCCESS;
}