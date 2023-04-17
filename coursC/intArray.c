#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intArray.h"

void intArray_debug(int *tab, int len)
{
    printf("[ ");
    for (int i = 0; i < len - 1; i++)
    {
        printf("%d, ", tab[i]);
    }
    printf("%d ", tab[len - 1]);
    printf(" ]\n");
}

void intArray_positive_values(int *tab, int len)
{
    printf("[ ");
    for (int i = 0; i < len; i++)
    {
        if (tab[i] >= 0)
            printf(" %d ", tab[i]);
    }
    printf(" ]\n");
}

bool intArray_search(int *tab, int len, int n)
{
    for (int i = 0; i < len; i++)
    {
        if (tab[i] == n)
        {
            return true;
        }
    }

    return false;
}

int intArray_nb_occurences(int *tab, int len, int n)
{
    int occur = 0;

    for (int i = 0; i < len; i++)
    {
        if (tab[i] == n)
        {
            occur++;
        }
    }

    return occur;
}

// --------------------------------------------------------------------- TEST MDULE --------------------------------------------------------------------------------

int main()
{

    int n;
    printf("Combien de cases voulez vous remplir ?");
    scanf("%d", &n);
    printf("\n");

    int *tab = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tab[i]);
    }

    intArray_debug(tab, n);

    intArray_positive_values(tab, n);

    int search = 21;

    if (intArray_search(tab, n, search))
    {
        printf("%d est present dans le tableau\n", search);
    }
    else
    {
        printf("%d n'est pas present dans le tableau\n", search);
    }

    printf("il y a %d occurrence de %d dans le tableau\n", intArray_nb_occurences(tab, n, search), search);

    free(tab);

    return EXIT_SUCCESS;
}