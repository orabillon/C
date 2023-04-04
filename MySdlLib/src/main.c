#include <stdlib.h>
#include "orn/orn_graphics.h"

int main(int argc, char *argv[])
{
    /* Permet l'affichage des printf sans tampons*/
    setvbuf(stdout, NULL,_IONBF, 0);

    /*
        variable
    */
    int iGameWidth = 1024;
    int iGameHeight = 768;

    if(!orn_graphics_init("Demo SDL", iGameWidth, iGameHeight, false))
    {
        return EXIT_FAILURE;
    };

    printf("Start\n");

    /* Variable Jeu*/
    orn_Texture texPlanet = orn_graphics_newImage("assets/images/planet.png");
    
    orn_Font font = orn_graphics_newFont("assets/fonts/Disney.ttf", 150);
    orn_Texture txtHello = orn_graphics_newText("coucou", font);

    /*
        Game Loop
    */
    while(true)
    {
        orn_graphics_setColor(0,0,0,255);
        if(orn_graphics_beginDraw() == 0)
        {
            break;
        };

        
        orn_graphics_draw(texPlanet,100,100);
        orn_graphics_draw(txtHello,0,0);

        orn_graphics_endDraw();
    }

    printf("Fin Programme\n");
    /*
        Nettoyage des pointeur
    */
    orn_graphics_freeImage(texPlanet);
    orn_graphics_freeImage(txtHello);
    orn_graphics_freeFont(font);
    orn_graphics_close();

    return EXIT_SUCCESS;
}
