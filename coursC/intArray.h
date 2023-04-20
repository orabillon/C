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

/**
 * creation d'un nouveau tableau d'entier (intarray) initialise a 0 pour chaque case
 * @param len taille du tableau
 * @return intarray retourne le nouveau tableau
 */
intarray intArray_create(int len);

/**
 * Permet d'afficher le contenu d'un tableau d'intarray
 * @param array tableau a afficher
 */
void intArray_debug(intarray array);

/**
 * Permet d'afficher les valeur positive d'un tableau d'intarray
 * @param array tableau a afficher
 */
void intArray_positive_values(intarray array);

/**
 * Permet de rechercher une valeur dans le contenu d'un tableau d'intarray
 * @param array tableau pour la recherche
 * @param n nombre a rechercher
 * @return retourn true si l'element est trouver sinon false.
 */
bool intArray_search(intarray array, int n);

/**
 * Compte le nombre d'occurrence d'une valeur contenu dans le tableau d'intarray
 * @param array tableau pour la recherche
 * @param n nombre a rechercher
 * @return le nombre d'occurrence de la valeur demandé
 */
int intArray_nb_occurences(intarray array, int n);

/**
 * Désaloue un tableau
 * @param array tableau a libéré
 */
void intArray_destroy(intarray array);

/**
 * Retourne la valeur contenu dans le tableau d'intarray a la case index
 * @param array tableau pour la recherche
 * @param index numero de la case dont on souhaite avoir le contenu
 * @return le nombre contenu dans la case numero 'index'
 */
int intArray_get(intarray array, int index);

/**
 * Place une valeur dans le tableau d'intarray a la case index
 * @param array tableau pour l'insertion
 * @param index numero de la case dont on souhaite modifier le contenu
 * @param value valeur a inserer dans le tableau a l'index indiquer
 */
void intArray_set(intarray array, int index, int value);

/**
 * Retourne la longueur d'un tableau d'intarray
 * @param array tableau pour le calcul de la taille
 * @return la taille du tableau
 */
int intArray_length(intarray array);

/**
 * Retourne un tableau d'intarray avec le contenu des deux passer en parametres
 * @param array1 premier tableau
 * @param array2 second tableau
 * @return un nouveau tableau contenant le contenu des deux passer en parametre
 */
intarray intArray_concat(intarray array1, intarray array2);

/**
 * Retourne l'index de l'element min un tableau d'intarray
 * @param array tableau pour la recherche du min
 * @return index de l'element min du tableau
 */
int intArray_get_index_min(intarray array);

/**
 * Retourne l'index de l'element min d'un tableau d'intarray depuis un index jusqu'a la fin
 * @param array tableau pour la recherche du min
 * @param index index de depart
 * @return index de l'élément min du tableau entre l'index et la fin
 */
int intArray_get_index_min_from(intarray array, int index);

/**
 * Retourne l'element min d'un tableau d'intarray
 * @param array tableau pour la recherche du min
 * @return Element min du tableau
 */
int intArray_get_min(intarray array);

/**
 * Retourne l'index de l'element max d'un tableau d'intarray
 * @param array tableau pour la recherche du max
 * @return index de l'element max du tableau
 */
int intArray_get_index_max(intarray array);

/**
 * Retourne l'index de l'element max d'un tableau d'intarray depuis un index jusqu'a la fin
 * @param array tableau pour la recherche du max
 * @param index index de depart
 * @return index de l'élément max du tableau entre l'index et la fin
 */
int intArray_get_index_max_from(intarray array, int index);

/**
 * Retourne l'element max d'un tableau d'intarray
 * @param array tableau pour la recherche du max
 * @return Element max du tableau
 */
int intArray_get_max(intarray array);

#endif