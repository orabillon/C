#ifndef __orn_graphics_h__
#define __orn_graphics_h__

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "orn_keyboard.h"

extern SDL_Renderer *orn_sdl_renderer;
extern float orn_dt;
extern int orn_iGameWidth;
extern int orn_iGameHeight;

/**
 * Represente une image
 * @param *sdl_texture Texture SDL2 de l'image
 * @param iWidth Largeur de l'image
 * @param iHeight Hauteur de l'image
 * @param bTransparency Prendre en compte la transparence pour la texture
 * @param uAlpha 0-255 - pourcentage de transparence de la couleur à appliquer
 * @param uRed   0-255 - pourcentage de rouge de la couleur à appliquer
 * @param uGreen 0-255 - pourcentage de vert de la couleur à appliquer
 * @param uBlue  0-255 - pourcentage de bleu de la couleur à appliquer
 * @param dAngle Angle de rotation
 * @param bIsFlipV flip vertical 
 * @param bIsFlipH flip horizontal
 */
typedef struct orn_Texture
{
    SDL_Texture *sdl_texture;
    int iWidth;
    int iHeight;
    bool bTransparency;
    Uint8 uAlpha;
    Uint8 uRed;
    Uint8 uGreen;
    Uint8 uBlue;
    double dAngle;
    bool bIsFlipV;
    bool bIsFlipH;
} orn_Texture;

/**
 * Represente une couleur
 * @param uRed   0-255 - pourcentage de rouge de la couleur à appliquer
 * @param uGreen 0-255 - pourcentage de vert de la couleur à appliquer
 * @param uBlue  0-255 - pourcentage de bleu de la couleur à appliquer
 * @param uAlpha 0-255 - pourcentage de transparence de la couleur à appliquer
 */
typedef struct orn_Couleur
{
    Uint8 uRed;
    Uint8 uGreen;
    Uint8 uBlue;
    Uint8 uAlpha;
} orn_Couleur;

/**
 * Represente un rectangle
 * @param x coordonnée x de l'origine
 * @param y coordonnée y de l'origine
 * @param w largeur du rectangle
 * @param h hauteur du rectangle
 */
typedef struct orn_rect
{
    int x;
    int y;
    int w;
    int h;
} orn_rect;

// initialisation et cloture SDL
bool orn_graphics_init(const char *szTitre, int iWindowWidth, int iWindowHeight, int iGameWidth, int iGameHeight, bool bFullScreen);
void orn_graphics_close(void);

// Game Loop
int orn_graphics_beginDraw(void);
void orn_graphics_endDraw(void);

// images
SDL_Texture *LoadTexture(const char *path);
orn_Texture orn_graphics_newImage(const char *path);
void orn_graphics_freeImage(orn_Texture *image);
void orn_graphics_draw(orn_Texture image, int iX, int iY);
void orn_graphics_drawQuad(orn_Texture image, orn_rect rectSource, int iX, int iY);
void orn_graphics_drawQuad_game(orn_Texture *tex, int iQuadW, int iQuadH, int iNumFrame, int iX, int iY);
void orn_graphics_SetTextureColor(orn_Texture *image, Uint8 uRed, Uint8 uGreen, Uint8 uBlue, Uint8 uAlpha);
void orn_graphics_SetTextureTransparency(orn_Texture *image, bool bTransparency, Uint8 uAlpha);
void orn_graphics_setTextureAngle(orn_Texture *image, double dAngle);
void orn_graphics_setTextureFlip(orn_Texture *image, bool bFlipV, bool bFlipH);

// Primitive
void orn_graphics_setColor(Uint8 iRed, Uint8 iGreen, Uint8 iBlue, Uint8 iAlpha);
void orn_graphics_line(int iX1, int iY1, int iX2, int iY2);
void orn_graphics_rectangle(const char *szMode, int iX, int iY, int iWidth, int iHeight);
void orn_graphics_circle(const char *szMode, int iCentreX, int iCentreY, int iRadius);

#endif