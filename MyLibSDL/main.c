#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SDL_ASSERT_LEVEL 2

SDL_Texture* LoadTexture(SDL_Renderer *renderer, char *path){
    SDL_Texture *texture = NULL;
    
    texture = IMG_LoadTexture(renderer, path);
    if (texture == NULL){
        printf("Impossible de créér la texture : %s  Erreur : %s \n", path, IMG_GetError());
        return NULL; 
    }
    return texture;
}


int main (int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Start \n");

    int iGameWidth = 1024, iGameHeight = 768;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL !\n");
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Titre fenêtre",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                iGameWidth,
                                                iGameHeight,
                                                SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        SDL_Log("Impossible de créér la fenêtre : %s \n", SDL_GetError());
        return -1; 
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_Log("Impossible de créér le rendu : %s \n", SDL_GetError());
        return -1; 
    }

    // Game Loop
    while(true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                break;
            }
        }

        // Efface l'écran
        SDL_RenderClear(renderer);

        // Présente l'écran
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}