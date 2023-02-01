#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main (int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL !\n");
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Titre fenêtre",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                640,
                                                480,
                                                SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        printf("Impossible de créér la fenêtre : %s \n", SDL_GetError());
        return -1; 
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        printf("Impossible de créér le rendu : %s \n", SDL_GetError());
        return -1; 
    }

    while(true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}