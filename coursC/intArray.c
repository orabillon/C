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

intarray intArray_concat(intarray array1, intarray array2)
{
    intarray concat = intArray_create(array1.len + array2.len);
    int j = 0;

    for (int i = 0; i < array1.len; i++)
    {
        concat.data[i] = array1.data[i];
        j++;
    }
    for (int i = 0; i < array2.len; i++)
    {
        concat.data[j] = array2.data[i];
        j++;
    }
    return concat;
}

int intArray_get_index_of_min(intarray array)
{
    return intArray_get_index_min_from(array, 0);
}

int intArray_get_min(intarray array)
{
    int index_mini = intArray_get_index_of_min(array);
    return array.data[index_mini];
}

int intArray_get_index_min_from(intarray array, int index)
{
    int mini = array.data[index];
    int index_mini = index;

    for (int i = index + 1; i < array.len; i++)
    {
        if (array.data[i] < mini)
        {
            mini = array.data[i];
            index_mini = i;
        }
    }

    return index_mini;
}

int intArray_get_index_of_max(intarray array)
{
    return intArray_get_index_max_from(array, 0);
}

int intArray_get_max(intarray array)
{
    int index_max = intArray_get_index_of_max(array);
    return array.data[index_max];
}

int intArray_get_index_max_from(intarray array, int index)
{
    int max = array.data[index];
    int index_max = index;

    for (int i = index + 1; i < array.len; i++)
    {
        if (array.data[i] > max)
        {
            max = array.data[i];
            index_max = i;
        }
    }

    return index_max;
}

// --------------------------------------------------------------------- TEST MDULE --------------------------------------------------------------------------------

int main()
{

    intarray array = intArray_create(8);
    intarray array2 = intArray_create(3);

    for (int i = 0; i < array.len; i++)
    {
        array.data[i] = 6 * i + 4;
    }

    for (int i = 0; i < array2.len; i++)
    {
        array2.data[i] = 12 * i + 14;
    }

    intArray_debug(array);
    printf("\n");
    intArray_debug(array2);
    printf("\n");

    intarray c = intArray_concat(array, array2);
    intArray_debug(c);
    printf("\n");

    printf("-- %d --", intArray_get_min(c));

    intArray_destroy(array);
    intArray_destroy(array2);
    intArray_destroy(c);

    return EXIT_SUCCESS;
}