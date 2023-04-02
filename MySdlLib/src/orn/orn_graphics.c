#include <stdlib.h>
#include "orn_graphics.h"

#define SDL_ASSERT_LEVEL 2

SDL_Window *orn_sdl_window;
SDL_Renderer *orn_sdl_renderer;

// initialisation et cloture SDL
bool orn_graphics_init( const char *szTitre, int iWidth, int iHeight, bool bFullScreen)
{
    Uint32 uFlagsWindos = SDL_WINDOW_SHOWN;
    Uint32 uFlagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    Uint32 uFlagsSdlImage = IMG_INIT_JPG | IMG_INIT_PNG;

    if(bFullScreen)
    {
        uFlagsWindos |= SDL_WINDOW_FULLSCREEN;
    }
    /*
        initialisation SDL
    */
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
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
        uFlagsWindos
    );

    if (orn_sdl_window == NULL){
        printf("Impossible de creer la fenetre : %s\n", SDL_GetError());
        return false;
    }

    /*
        création renderer
    */
    orn_sdl_renderer = SDL_CreateRenderer(orn_sdl_window,-1,uFlagsRenderer);
    if (orn_sdl_renderer == NULL){
        printf("Impossible de creer le renderer : %s\n", SDL_GetError());
        return false;
    }
    else
    {
        /* Initialisation SDL IMAGE*/
        if(!(IMG_Init(uFlagsSdlImage) & uFlagsSdlImage)){
            printf("Impossible d'initialiser la librairie SDL_IMAGE : %s\n", IMG_GetError());
        return false;
        } 
    }
    
    return true;
}

void orn_graphics_close(void)
{
    SDL_DestroyRenderer(orn_sdl_renderer);
    SDL_DestroyWindow(orn_sdl_window);

    /* Fermeture SDL*/
    IMG_Quit();
    SDL_Quit();
}

// Game Loop
int orn_graphics_beginDraw(void)
{
    /*Parcour des évenement SDL*/
    SDL_Event event;
    if (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
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

    Texture= IMG_LoadTexture(orn_sdl_renderer, path);
    if(Texture == NULL){
        printf("Impossible de creer la texture a partir de %s erreur : %s\n", path, IMG_GetError());
        return NULL;
    }

    return Texture;
}

orn_Texture orn_graphics_newImage(const char *path)
{
    orn_Texture tex;

    tex.sdl_texture = LoadTexture(path);
    if(tex.sdl_texture == NULL)
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
    if(image.sdl_texture != NULL)
    {
        SDL_DestroyTexture(image.sdl_texture);
        image.sdl_texture = NULL;
    }
}

