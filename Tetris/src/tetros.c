#include "tetros.h"
#include <stdio.h>

void test(){

    tetros myTetros;

     
     int tableau[2][4][4] = {
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    }
    };

    myTetros.tabTetros = tableau;

    printf("%d", myTetros.tabTetros[1][2][1]);

}