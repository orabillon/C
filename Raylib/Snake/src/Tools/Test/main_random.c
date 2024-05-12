#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "orn_random.h"

int main() {
    double min = 5.0; 
    double max = 10.0; 
    double nombreAleatoire;
    
    int imin = 5;
    int imax = 10;
    int inombreAleatoire;

    orn_random_init(0);
    
    for (int i = 0; i<10; i++)
    {
        nombreAleatoire = orn_random_nextDouble(min, max); 
        printf("Nombre réel aléatoire entre %.2f et %.2f : %.2f\n", min, max, nombreAleatoire);
    }

    for (int i = 0; i<10; i++)
    {
        inombreAleatoire = orn_random_nextInt(imin, imax); 
        printf("Nombre aléatoire entre %d et %d : %d\n", imin, imax, inombreAleatoire); 
    }

    int bornMax = 100;
    for (int i = 0; i<10; i++)
    {
        inombreAleatoire = orn_random_borneMaxInt(bornMax); 
        printf("Nombre aléatoire entre 0 et %d : %d\n", bornMax, inombreAleatoire); 
    }

    double bMax = 100;

    for (int i = 0; i<10; i++)
    {
        nombreAleatoire = orn_random_borneMaxDouble(bornMax); 
        printf("Nombre aléatoire entre 0 et %.2f : %.2f\n", bMax, nombreAleatoire); 
    }


    for (int i = 0; i<10; i++)
    {
        inombreAleatoire = orn_random_lancerDe(20); 
        printf("Nombre du de a 20 : %d\n", inombreAleatoire); 
    }

    return 0;
}