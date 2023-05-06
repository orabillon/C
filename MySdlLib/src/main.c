#include <stdlib.h>
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn.h"
#include "game.h"

int main(int argc, char *argv[])
{
    /* Permet l'affichage des printf sans tampons*/
    setvbuf(stdout, NULL, _IONBF, 0);

    /*
        variable
    */
    int iGameWidth = 256;
    int iGameHeight = 192;
    int iWindowWidth = 1024;
    int iWindowHeight = 768;

    if (!orn_graphics_init("Demo SDL", iWindowWidth, iWindowHeight, iGameWidth, iGameHeight, false))
    {
        return EXIT_FAILURE;
    };

    _orn_keyboard_init();

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

        game_update();
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
