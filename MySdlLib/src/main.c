#include <stdlib.h>
#include "orn/orn_graphics.h"
#include "orn/orn.h"
#include "game.h"
#include "orn/orn_param.h"

int main(int argc, char *argv[])
{
    /* Permet l'affichage des printf sans tampons*/
    setvbuf(stdout, NULL, _IONBF, 0);

    if (!orn_graphics_init(TITRE_JEU, FENETRE_WIDTH, FENETRE_HEIGHT, JEU_WIDTH, JEU_HEIGHT, PLEIN_ECRAN))
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
