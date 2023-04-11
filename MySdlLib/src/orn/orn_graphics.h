#ifndef __orn_graphics_h__
#define __orn_graphics_h__

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

extern SDL_Renderer *orn_sdl_renderer;

typedef struct orn_Texture
{
    SDL_Texture *sdl_texture;
    int iWidth;
    int iHeight;

} orn_Texture;


// initialisation et cloture SDL
bool orn_graphics_init(const char *szTitre, int iWidth, int iHeight, bool bFullScreen);
void orn_graphics_close(void);

// Game Loop
int orn_graphics_beginDraw(void);
void orn_graphics_endDraw(void);

// images
SDL_Texture *LoadTexture(const char *path);
orn_Texture orn_graphics_newImage(const char *path);
void orn_graphics_freeImage(orn_Texture image);
void orn_graphics_draw(orn_Texture image, int iX, int iY);

// Primitive
void orn_graphics_setColor(Uint8 iRed, Uint8 iGreen, Uint8 iBlue, Uint8 iAlpha);
void orn_graphics_line(int iX1, int iY1, int iX2, int iY2);
void orn_graphics_rectangle(const char *mode, int iX, int iY, int iW, int iH);
void orn_graphics_circle(const char *szMode, int iCentreX, int iCentreY, int iRadius);


#endif