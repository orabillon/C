#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"
#include "orn/orn_sound.h"

/* Variable Jeu*/
orn_Texture texPlanet;
orn_Texture textDt;
orn_Font font;
orn_son son;
orn_fx fx;
int posX;
int posY;

void game_load(void)
{
    /* Variable Jeu*/
    texPlanet = orn_graphics_newImage("assets/images/planet.png");
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    posX = 100;
    posY = 100;

    son = orn_sound_musique_new("assets/sons/Spiritual.mp3");
    fx = orn_sound_fx_new("assets/sons/Coin.wav");

    orn_sound_musique_play(&son, -1);
}

void game_update(void)
{
    if (orn_keyboard_isDown("a"))
    {
        posX++;
    }
    if (orn_keyboard_KeyPressed("left"))
    {
        posX -= 20;
    }

    if (orn_keyboard_isDown("up"))
    {
        posY--;
    }
    if (orn_keyboard_isDown("down"))
    {
        posY++;
    }
    if (orn_keyboard_KeyPressed("p"))
    {
        orn_sound_fx_play(-1, &fx, 1);
    }
    if (orn_keyboard_KeyPressed("r"))
    {
        orn_sound_musique_resume();
    }
    if (orn_keyboard_KeyPressed("s"))
    {
        orn_sound_musique_stop();
    }
}

void game_draw(void)
{
    orn_graphics_SetTextureColor(&texPlanet, 0, 255, 0, 0);
    orn_graphics_SetTextureTransparency(&texPlanet, true, 50);
    orn_graphics_draw(texPlanet, posX, posY);

    char sDT[255];
    sprintf(sDT, "%f", orn_dt);
    textDt = orn_font_newText(sDT, font);
    orn_graphics_SetTextureColor(&textDt, 255, 0, 0, 0);
    orn_graphics_draw(textDt, 50, 50);
}

void game_close(void)
{
    orn_graphics_freeImage(texPlanet);
    orn_graphics_freeImage(textDt);
    orn_sound_musique_delete(&son);
    orn_sound_fx_delete(&fx);
    orn_graphics_close();
}