#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


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
int orn_random_nextInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

/**
* Fonction pour générer un nombre aléatoire entre min et max inclus
* @param double Borne min 
* @param double Borne max inclus dans le tirage
* @return nombre entier 
*/
double orn_random_nextDouble(double min, double max) {
    double nombreAleatoire;
    double r = orn_random_0_1();

    // Met à l'échelle le nombre réel dans la plage spécifiée
    nombreAleatoire = min + r * (max - min);
    
    return nombreAleatoire;
}

/**
* Fonction pour générer un nombre aléatoire entre 0 et max inclus
* @param max Borne max inclus dans le tirage
* @return nombre entier 
*/
int orn_random_borneMaxInt(int max)
{
    return rand() % (max + 1);
}

/**
* Fonction pour générer un nombre réel aléatoire entre 0 et 1
*/
double orn_random_0_1() {
    double r = (double)rand() / RAND_MAX; 
    return r;
}

/**
* Fonction pour générer un nombre aléatoire entre 0 et max inclus
* @param max Borne max inclus dans le tirage
* @return nombre entier 
*/
double orn_random_borneMaxDouble(double max)
{
    double r = orn_random_0_1();
    return r * max;
}

/**
* Fonction pour simuler le lancer d'un dé à faces faces
* @param faces Nombre de face du de
* @return nombre entier 
*/
int orn_random_lancerDe(int faces) {
    return (rand() % faces) + 1; 
}