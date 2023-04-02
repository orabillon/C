#ifndef __orn_graphics_h__
#define __orn_graphics_h__

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"

typedef struct orn_Texture
{
    SDL_Texture *sdl_texture;
    int iWidth;
    int iHeight;

} orn_Texture;



bool orn_graphics_init(const char *szTitre, int iWidth, int iHeight, bool bFullScreen);
void orn_graphics_close(void);

int orn_graphics_beginDraw(void);
void orn_graphics_endDraw(void);
void orn_graphics_draw(orn_Texture image, int iX, int iY);

SDL_Texture *LoadTexture(const char *path);
orn_Texture orn_graphics_newImage(const char *path);
void orn_graphics_freeImage(orn_Texture image);

#endif