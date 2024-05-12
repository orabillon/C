#include <stdio.h>
#include "orn_lists.h"

// Fonction pour afficher un entier
void printInt(void* data) {
    printf("%d", *((int*)data));
}

// Fonction de comparaison pour le tri des entiers
int compareInt(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Fonction de prédicat pour filtrer les nombres pairs
int isEven(void* data) {
    int value = *((int*)data);
    return value % 2 == 0;
}

int main() {

    _orn_memory_init();

    // Création d'une nouvelle liste
    List* my_list = orn_list_newList();

    // Ajout d'entiers à la liste
    for (int i = 1; i <= 10; i++) {
        int* value = (int*)malloc(sizeof(int));
        *value = i;
        my_list = orn_list_addBack(my_list, value);
    }

    // Affiche l'element a l'index 3
    printf("contenu a l'index 3 : %d \n", *((int*)orn_list_getAtIndex(my_list,2)));

    // Affichage de la liste
    printf("Contenu de la liste :\n");
    orn_list_print(my_list, ", ", printInt);

    //orn_list_shuffle(my_list);
    //orn_list_print(my_list, ", ", printInt);
    
    // Tri de la liste
    List* my_list2 = orn_list_filter(my_list, isEven);
    orn_list_print(my_list2, ", ", printInt);

    // Libération de la mémoire allouée pour les éléments de la liste
    my_list = orn_list_clear(my_list);
    my_list2 = orn_list_clear(my_list2);

    orn_memory_check();

    return 0;
}


