#include <stdlib.h>
#include <assert.h>
#include "orn_graphics.h"
#include "orn_font.h"

#define SDL_ASSERT_LEVEL 2

/**
 * créer une police
 * @param *path Chemin de la font
 * @param iSize taille de la font
 * @return   retourne une orn_font
 */
orn_Font orn_font_newFont(const char *path, int iSize)
{
    orn_Font font = {NULL};

    font.sdl_font = TTF_OpenFont(path, iSize);

    if (font.sdl_font == NULL)
    {
        printf("Impossible de creer la font  %s erreur : %s\n", path, TTF_GetError());
    }

    return font;
}

/**
 * créer une orn_texture a partire du texte et de la font
 * @param *text texte à affiche
 * @param font font a utiliser pour la création de la texture
 * @return   retourne une orn_texture
 */
orn_Texture orn_font_newText(const char *texte, orn_Font font)
{
    assert(font.sdl_font != NULL);

    orn_Texture texture = {NULL, 0, 0};
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 255};

    surface = TTF_RenderUTF8_Solid(font.sdl_font, texte, textColor);
    texture.sdl_texture = SDL_CreateTextureFromSurface(orn_sdl_renderer, surface);
    texture.iWidth = surface->w;
    texture.iHeight = surface->h;
    texture.uAlpha = 255;
    texture.uBlue = 255;
    texture.uGreen = 255;
    texture.uRed = 255;
    texture.bTransparency = false;
    texture.bIsFlipH = false;
    texture.bIsFlipV = false;
    texture.dAngle = 0;
    SDL_FreeSurface(surface);

    return texture;
}

/**
 * Supprime une police
 * @param font orn_font a supprimer
 */
void orn_font_freeFont(orn_Font *font)
{
    TTF_CloseFont(font->sdl_font);
}
