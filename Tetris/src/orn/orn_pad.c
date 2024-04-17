#include "SDL.h"
#include "orn_pad.h"
#include <stdio.h>

SDL_GameController* padController;

/**
 * Initialise la manette 
 */
void _orn_pad_init(void){
    // Charger le premier contrôleur de jeu disponible
    padController = SDL_GameControllerOpen(0);
    if (padController == NULL) {
        printf("Aucun controleur de jeu n'a ete trouve.\n");
    }
}

/**
 * libere les ressources du pad
 */
void _orn_pad_close(void)
{
    if (padController != NULL) 
    {
        SDL_GameControllerClose(padController);
    }
}

/**
 * Met a joour la structure GameControllerState
 * @param controller Controleur dont on veut recuperer le statut
 * @param state structure pour la sauvegarde
 */
void updateControllerState(SDL_GameController* controller, GameControllerState* state)
{
     // Mise à jour de l'état des boutons
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        state->buttons[i] = SDL_GameControllerGetButton(controller, i);
    }

    // Mise à jour de l'état des axes analogiques
    state->axisLeftX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
    state->axisLeftY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
    state->axisRightX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
    state->axisRightY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
}

/**
 * Permet de copier la structure dans une seconde. Permet la mise en place d'une structure old 
 * @param source structure a copier
 * @param destination structure pour la copie
 */
void copyControllerState(const GameControllerState* source, GameControllerState* destination) {
    // Copie de l'état des boutons
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        destination->buttons[i] = source->buttons[i];
    }

    // Copie de l'état des axes analogiques
    destination->axisLeftX = source->axisLeftX;
    destination->axisLeftY = source->axisLeftY;
    destination->axisRightX = source->axisRightX;
    destination->axisRightY = source->axisRightY;
}

