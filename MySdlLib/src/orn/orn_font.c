#include <stdlib.h>
#include <assert.h>
#include "orn_graphics.h"
#include "orn_font.h"

#define SDL_ASSERT_LEVEL 2


orn_Font orn_font_newFont(const char *path, int iSize)
{
    orn_Font font = {NULL};
    
    font.sdl_font = TTF_OpenFont(path, iSize);

    if(font.sdl_font == NULL)
    {
        printf("Impossible de creer la font  %s erreur : %s\n", path, TTF_GetError());
    }

    return font;
}

orn_Texture orn_font_newText(const char *texte, orn_Font font)
{
    assert(font.sdl_font != NULL);

    orn_Texture texture = {NULL,0,0};
    SDL_Surface *surface;
    SDL_Color textColor = {255,255,255,255}; 

    surface = TTF_RenderUTF8_Solid(font.sdl_font, texte, textColor);
    texture.sdl_texture = SDL_CreateTextureFromSurface(orn_sdl_renderer, surface);
    texture.iWidth = surface->w;
    texture.iHeight = surface->h;
    SDL_FreeSurface(surface);

    return texture;
}

void orn_font_freeFont(orn_Font font)
{
    TTF_CloseFont(font.sdl_font);
}

