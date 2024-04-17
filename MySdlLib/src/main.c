#include <stdlib.h>
#include "orn/orn_graphics.h"
#include "orn/orn.h"
#include "game.h"

int main(int argc, char *argv[])
{
    /* Permet l'affichage des printf sans tampons*/
    setvbuf(stdout, NULL, _IONBF, 0);

    /*
        variable
    */
    int iGameWidth = 320;
    int iGameHeight = 200;
    int iWindowWidth = iGameWidth * 3;
    int iWindowHeight = iGameHeight * 3;

    if (!orn_graphics_init("Demo SDL", iWindowWidth, iWindowHeight, iGameWidth, iGameHeight, false))
    {
        return EXIT_FAILURE;
    };

    orn_init();
    

    printf("Start\n");

    /*
    Game Loop
*/
    game_load();

    while (true)
    {
        orn_graphics_setColor(0, 0, 0, 255);
        if (orn_graphics_beginDraw() == 0)
        {
            break;
        };

        game_update(orn_dt);
        game_draw();

        orn_graphics_endDraw();
    }

    /*
    Nettoyage des pointeur
*/
    game_close();
    
    orn_close();

    printf("Fin Programme\n");

    return EXIT_SUCCESS;
}
