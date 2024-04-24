#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn_sound.h"
#include "orn/orn_lists.h"
#include "tetros.h"
#include <math.h>

List* Tetrominos;

void funPrint (void* data){

    //int valeur = ((tetros*)data)->tabTetros[1][2][1];
    //printf(" fonction pointe %d ", valeur);
    printf("toto");
}

void game_load(void)
{
    
    Tetrominos = orn_list_newList();
    
    tetros *TetrosOne = NULL;

     
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

    TetrosOne->tabTetros = tableau;
    printf("totot");
   // Tetrominos = orn_list_addBack(Tetrominos,TetrosOne);

  //  orn_list_print(Tetrominos," - ", &funPrint);

  //  printf("%d \n", TetrosOne->tabTetros[1][2][1]);
}

void game_reset(void){

}

void game_update(float dt)
{
    
}

void game_draw(void)
{
   
}

void game_close(void)
{
    
}