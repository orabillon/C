#include <stdlib.h>
#include <assert.h>
#include "orn_graphics.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *orn_sdl_window;
SDL_Renderer *orn_sdl_renderer;

// initialisation et cloture SDL
bool orn_graphics_init(const char *szTitre, int iWidth, int iHeight, bool bFullScreen)
{
    Uint32 uFlagsWindos = SDL_WINDOW_SHOWN;
    Uint32 uFlagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    Uint32 uFlagsSdlImage = IMG_INIT_JPG | IMG_INIT_PNG;

    if (bFullScreen)
    {
        uFlagsWindos |= SDL_WINDOW_FULLSCREEN;
    }
    /*
        initialisation SDL
    */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL\n");
        return false;
    }

    /*
        création fenêtre
    */
    orn_sdl_window = SDL_CreateWindow(
        szTitre,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        iWidth,
        iHeight,
        uFlagsWindos);

    if (orn_sdl_window == NULL)
    {
        printf("Impossible de creer la fenetre : %s\n", SDL_GetError());
        return false;
    }

    /*
        création renderer
    */
    orn_sdl_renderer = SDL_CreateRenderer(orn_sdl_window, -1, uFlagsRenderer);
    if (orn_sdl_renderer == NULL)
    {
        printf("Impossible de creer le renderer : %s\n", SDL_GetError());
        return false;
    }
    else
    {
        /* Initialisation SDL IMAGE*/
        if (!(IMG_Init(uFlagsSdlImage) & uFlagsSdlImage))
        {
            printf("Impossible d'initialiser la librairie SDL_IMAGE : %s\n", IMG_GetError());
            return false;
        }
    }

    /* Initialisation SDL_TTF*/
    if (TTF_Init() == -1)
    {
        printf("Impossible d'initialiser la librairie SDL_TTF : %s\n", TTF_GetError());
        return false;
    }

    // Permet d'activer le melange des couleur et l'alpha
    SDL_SetRenderDrawBlendMode(orn_sdl_renderer, SDL_BLENDMODE_BLEND);

    return true;
}

void orn_graphics_close(void)
{
    SDL_DestroyRenderer(orn_sdl_renderer);
    SDL_DestroyWindow(orn_sdl_window);

    /* Fermeture SDL*/
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

// Game Loop
int orn_graphics_beginDraw(void)
{
    /*Parcour des évenement SDL*/
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 0;
        }
    }

    /* Efface l'écran */
    SDL_RenderClear(orn_sdl_renderer);

    return 1;
}

void orn_graphics_endDraw(void)
{
    /* Affiche l'écran*/
    SDL_RenderPresent(orn_sdl_renderer);
    orn_keyboard_old();
}

void orn_graphics_draw(orn_Texture image, int iX, int iY)
{
    SDL_Rect recDestination = {iX, iY, image.iWidth, image.iHeight};
    SDL_RenderCopy(orn_sdl_renderer, image.sdl_texture, NULL, &recDestination);
}

// images

SDL_Texture *LoadTexture(const char *path)
{

    SDL_Texture *Texture = NULL;

    Texture = IMG_LoadTexture(orn_sdl_renderer, path);
    if (Texture == NULL)
    {
        printf("Impossible de creer la texture a partir de %s erreur : %s\n", path, IMG_GetError());
        return NULL;
    }

    return Texture;
}

orn_Texture orn_graphics_newImage(const char *path)
{
    orn_Texture tex = {NULL, 0, 0};

    tex.sdl_texture = LoadTexture(path);
    if (tex.sdl_texture == NULL)
    {
        printf("Impossible de charger la texture a partir de %s erreur : %s\n", path, IMG_GetError());
    }
    else
    {
        SDL_QueryTexture(tex.sdl_texture, NULL, NULL, &tex.iWidth, &tex.iHeight);
    }

    return tex;
}

void orn_graphics_freeImage(orn_Texture image)
{
    if (image.sdl_texture != NULL)
    {
        SDL_DestroyTexture(image.sdl_texture);
        image.sdl_texture = NULL;
    }
}

// Primitive

void orn_graphics_setColor(Uint8 uRed, Uint8 uGreen, Uint8 uBlue, Uint8 uAlpha)
{
    SDL_SetRenderDrawColor(orn_sdl_renderer, uRed, uGreen, uBlue, uAlpha);
}

void orn_graphics_line(int iX1, int iY1, int iX2, int iY2)
{
    SDL_RenderDrawLine(orn_sdl_renderer, iX1, iY1, iX2, iY2);
}

void orn_graphics_rectangle(const char *mode, int iX, int iY, int iW, int iH)
{
    SDL_Rect rect;
    rect.h = iH;
    rect.w = iW;
    rect.x = iX;
    rect.y = iY;

    if (strcmp(mode, "line") == 0)
    {
        SDL_RenderDrawRect(orn_sdl_renderer, &rect);
    }
    else if (strcmp(mode, "fill") == 0)
    {
        SDL_RenderFillRect(orn_sdl_renderer, &rect);
    }
}

void orn_graphics_circle(const char *szMode, int iCentreX, int iCentreY, int iRadius)
{

    if (strcmp("line", szMode) == 0)
    {
        const int diameter = (iRadius * 2);

        int x = (iRadius - 1);
        int y = 0;
        int tx = 1;
        int ty = 1;
        int error = (tx - diameter);

        while (x >= y)
        {
            // Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + x, iCentreY - y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + x, iCentreY + y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - x, iCentreY - y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - x, iCentreY + y);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + y, iCentreY - x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX + y, iCentreY + x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - y, iCentreY - x);
            SDL_RenderDrawPoint(orn_sdl_renderer, iCentreX - y, iCentreY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }
    if (strcmp("fill", szMode) == 0)
    {
        int offsetx, offsety, d;
        int status;

        offsetx = 0;
        offsety = iRadius;
        d = iRadius - 1;
        status = 0;

        while (offsety >= offsetx)
        {

            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsety, iCentreY + offsetx, iCentreX + offsety, iCentreY + offsetx);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsetx, iCentreY + offsety, iCentreX + offsetx, iCentreY + offsety);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsetx, iCentreY - offsety, iCentreX + offsetx, iCentreY - offsety);
            status += SDL_RenderDrawLine(orn_sdl_renderer, iCentreX - offsety, iCentreY - offsetx, iCentreX + offsety, iCentreY - offsetx);

            if (status < 0)
            {
                status = -1;
                break;
            }

            if (d >= 2 * offsetx)
            {
                d -= 2 * offsetx + 1;
                offsetx += 1;
            }
            else if (d < 2 * (iRadius - offsety))
            {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else
            {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
    }
}
