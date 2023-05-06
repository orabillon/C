#include "game.h"
#include "orn/orn_graphics.h"
#include "orn/orn_font.h"
#include "orn/orn_keyboard.h"

/* Variable Jeu*/
orn_Texture texPlanet;
orn_Texture textDt;
orn_Font font;
int posX;
int posY;

void game_load(void)
{
    /* Variable Jeu*/
    texPlanet = orn_graphics_newImage("assets/images/planet.png");
    font = orn_font_newFont("assets/fonts/Open24.ttf", 35);
    posX = 100;
    posY = 100;
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
}

void game_draw(void)
{
    orn_graphics_draw(texPlanet, posX, posY);

    char sDT[255];
    sprintf(sDT, "%f", orn_dt);
    textDt = orn_font_newText(sDT, font);
    orn_graphics_draw(textDt, 50, 50);
}

void game_close(void)
{
    orn_graphics_freeImage(texPlanet);
    orn_graphics_freeImage(textDt);
    orn_graphics_close();
}