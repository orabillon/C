#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn_sound.h"
#include "orn/orn_animation.h"
#include "orn/orn_lists.h"
#include <math.h>

/* Variable Jeu*/
orn_Font font;
orn_Texture texIndiana;
orn_Texture texIndiana2;
orn_Texture Vaisseau;

orn_Texture Texte;

orn_animation *Indiana;

orn_listAnimation *listeAnimation;

orn_son Musique;
orn_fx Fx;


void game_load(void)
{
    /* Variable Jeu*/
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    texIndiana = orn_graphics_newImage("assets/images/indiana.png");
    texIndiana2 = orn_graphics_newImage("assets/images/indiana.png");
    Vaisseau = orn_graphics_newImage("assets/images/player.png");
    listeAnimation = orn_list_listeAnimation_newList();

    unsigned char test[] = {0,1,2,3,4,5,6,7};
    Indiana = orn_animation_createAnimation(&texIndiana2,"WALK",25,24,test,8,0.15f,true,true);
    Texte = orn_font_newText("Ceci est un Téxt¨^e",font);
    orn_graphics_setTextureFlip(&Texte, true, true );
    orn_graphics_setTextureAngle(&Texte, 90);
    orn_graphics_setTextureFlip(&texIndiana2, false, true);
    orn_graphics_setTextureAngle(&texIndiana2, 25);
    
    orn_graphics_SetTextureColor(&Texte,150,2,66,255);

    Musique = orn_sound_musique_new("assets/sons/Spiritual.mp3");
    orn_sound_musique_volume(23);
    orn_sound_musique_play(&Musique,1);

    Fx = orn_sound_fx_new("assets/sons/Coin.wav");
}

void game_update(float dt)
{
    orn_animation_updateAnimation(Indiana);

    if(orn_keyboard_KeyPressed("space"))
    {
        orn_sound_fx_play(-1,&Fx,2);
    }
}

void game_draw(void)
{
    orn_graphics_drawQuad_game(&texIndiana, 25, 24, 0, 15, 15);
    orn_graphics_drawQuad_game(&Vaisseau, 30, 16, 12, 50, 50);

    orn_graphics_draw(Texte, 15, 150);

    orn_animation_drawAnimation(Indiana,150,150);
}

void game_close(void)
{
    orn_animation_freeAnimation(Indiana);
    orn_font_freeFont(font);
    orn_graphics_freeImage(Texte);
    orn_graphics_freeImage(texIndiana);
    orn_graphics_freeImage(texIndiana2);
    orn_graphics_freeImage(Vaisseau);
    orn_list_listeAnimation_freeList(listeAnimation);
    orn_sound_musique_delete(&Musique);
    orn_sound_fx_delete(&Fx);
    orn_graphics_close();
}