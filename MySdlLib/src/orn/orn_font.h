#ifndef __orn_font_h__
#define __orn_font_h__

#include <stdio.h>
#include <stdbool.h>
#include "orn_graphics.h"
#include "SDL_ttf.h"

/**
 * Structure orn_font
 * @param  *sdl_font font SDL
 */
typedef struct orn_Font
{
    TTF_Font *sdl_font;
} orn_Font;

// Font et Texte
orn_Font orn_font_newFont(const char *path, int iSize);
orn_Texture orn_font_newText(const char *texte, orn_Font font);
void orn_font_freeFont(orn_Font font);

#endif
