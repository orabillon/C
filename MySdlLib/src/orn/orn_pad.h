#ifndef __ORN_PAD_H__
#define __ORN_PAD_H__

#include "SDL.h"
#include <stdio.h>

extern SDL_GameController* padController;

#define NUM_BUTTONS SDL_CONTROLLER_BUTTON_MAX

/**
 * Represente l'etat du pad a un instant t
 * @param buttons Tableau pour stocker l'état de chaque bouton
 * @param axisRightX axe joystic droit
 * @param axisRightY axe joystic droit
 * @param axisLeftX axe joystic gauche
 * @param axisLeftY axe joystic gauche
 */
typedef struct {
    // Tableau pour stocker l'état de chaque bouton
    int buttons[NUM_BUTTONS];

    // Valeurs des axes analogiques
    Sint16 axisRightX;
    Sint16 axisRightY;
    Sint16 axisLeftX;
    Sint16 axisLeftY;

} GameControllerState;

void _orn_pad_init(void);
void _orn_pad_close(void);

void updateControllerState(SDL_GameController* controller, GameControllerState* state);
void copyControllerState(const GameControllerState* source, GameControllerState* destination);

#endif