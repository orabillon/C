#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn_sound.h"
#include "orn/orn_animation.h"
#include <math.h>

/* Variable Jeu*/
orn_Font font;
orn_Texture texIndiana;
orn_Texture Vaisseau;

orn_animation *Indiana;



/* ------------------------------------------------------------------------------------------------------------------------------------------------- */

void game_load(void)
{
    /* Variable Jeu*/
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    texIndiana = orn_graphics_newImage("assets/images/indiana.png");
    Vaisseau = orn_graphics_newImage("assets/images/player.png");

    unsigned char test[] = {0,1,2,3,4,5,6,7};
    Indiana = orn_animation_createAnimation(&texIndiana,"WALK",25,24,test,8,0.15f,true,true);

}

void game_update(float dt)
{
    orn_animation_updateAnimation(Indiana);
}

void game_draw(void)
{
    orn_graphics_drawQuad_game(&texIndiana, 25, 24, 0, 15, 15);
    orn_graphics_drawQuad_game(&Vaisseau, 30, 16, 12, 50, 50);

    orn_animation_drawAnimation(Indiana,150,150);

    
}

void game_close(void)
{
    orn_animation_freeAnimation(Indiana);
    orn_font_freeFont(font);
    orn_graphics_freeImage(texIndiana);
    orn_graphics_freeImage(Vaisseau);
    orn_graphics_close();
}