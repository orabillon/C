#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

#define SDL_ASSERT_LEVEL 2

SDL_Texture *LoadTexture(SDL_Renderer *renderer, char *path){

    SDL_Texture *texture = NULL;

    texture = IMG_LoadTexture(renderer, path);
    if(texture == NULL){
        printf("Impossible de creer la texture a partir de %s erreur : %s\n", path, IMG_GetError());
        return NULL;
    }

    return texture;
}

int main(int argc, char *argv[]){
    /* Permet l'affichage des printf sans tampons*/
    setvbuf(stdout, NULL,_IONBF, 0);

    /*
        variable
    */
    int iGameWidth = 1024;
    int iGameHeight = 768;

    Uint32 uFlagsWindos = SDL_WINDOW_SHOWN;
    Uint32 uFlagsRenderer = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    Uint32 uFlagsSdlImage = IMG_INIT_JPG | IMG_INIT_PNG;

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
    else
    {
        /* Initialisation SDL IMAGE*/
        if(!(IMG_Init(uFlagsSdlImage) & uFlagsSdlImage)){
            printf("Impossible d'initialiser la librairie SDL_IMAGE : %s\n", IMG_GetError());
        return -1;
        } 
    }

   printf("Start");

   /* Variable Jeu*/
    SDL_Texture *texPlanet = LoadTexture(renderer, "assets/images/planet.png");

    int texPlanetWidth = 0;
    int textPlanetHeight = 0;
    SDL_QueryTexture(texPlanet, NULL, NULL, &texPlanetWidth, &textPlanetHeight);
    SDL_Rect recDestination = {0, 0, texPlanetWidth, textPlanetHeight};

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

        /* Modification de l'écran */
        SDL_RenderCopy(renderer, texPlanet, NULL, &recDestination);

        /* Affiche l'écran*/
        SDL_RenderPresent(renderer);
   }

    printf("Fin Programme");
   /*
        Nettoyage des pointeur
   */
   SDL_DestroyTexture(texPlanet);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

   /* Fermeture SDL*/
   IMG_Quit();
   SDL_Quit();

   return 0;
}
