#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

int main(int argc, char *argv[]){
    /*
        variable
    */
    int iGameWidth = 1024;
    int iGameHeight = 768;

    Uint32 uFlagsWindos = SDL_WINDOW_SHOWN;
    Uint32 uFlagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    /*
        initialisation SDL
    */
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL\n");
        return -1;
    }

    /*
        création fenêtre
    */
    SDL_Window *window = SDL_CreateWindow(
        "Titre du programe",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        iGameWidth,
        iGameHeight,
        uFlagsWindos
    );

    if (window == NULL){
        printf("Impossible de creer la fenetre : %s\n", SDL_GetError());
        return -1;
    }

    /*
        création renderer
    */
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,uFlagsRenderer);
    if (renderer == NULL){
        printf("Impossible de creer le renderer : %s\n", SDL_GetError());
        return -1;
    }

    /*
        Game Loop
    */
   while(true)
   {
        /*Parcour des évenement SDL*/
        SDL_Event event;
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                break;
            }
        }

        /* Efface l'écran */
        SDL_RenderClear(renderer);

        /* Affiche l'écran*/
        SDL_RenderPresent(renderer);
   }

   /*
        Nettoyage des pointeur
   */
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

   /* Fermeture SDL*/
   SDL_Quit();

   return 0;
}
