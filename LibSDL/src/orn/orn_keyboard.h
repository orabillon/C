#ifndef __orn_keyboard_h__
#define __orn_keyboard_h__

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * Structure orn_sdlkey representant une touche du clavier
 * @param  *key Type de la touche (ex a / b / "right" ...)
 * @param   sdl_scancode Code SDL de la touche
 */
typedef struct orn_sdlkey
{
    char *key; // "a", "right", ...
    SDL_Scancode sdl_scancode;
} orn_sdlkey;

extern const Uint8 *_orn_sdl_keystate;

void _orn_keyboard_init(void);
void _orn_keyboard_close(void);
void orn_keyboard_old(void);

bool orn_keyboard_isDown(const char *key);
bool orn_keyboard_KeyPressed(const char *key);

#endif