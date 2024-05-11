#include <stdbool.h>
#include <time.h>

#include "orn_random.h"

/**
* Fonction pour initialiser le générateur de nombres aléatoires
* @param graine graine pour la generation, 0 pour ne pas definir de graine specifique
*/
void orn_random_init( unsigned int graine){
    if (graine == 0)
    {
        srand(time(NULL));
    }
    else
    {
        srand(graine);
    }
}


/**
* Fonction pour générer un nombre aléatoire entre min et max inclus
* @param min Borne min 
* @param max Borne max inclus dans le tirage
* @return nombre entier 
*/
int genererNombreAleatoire(int min, int max) {
    return min + rand() % (max - min + 1);
}