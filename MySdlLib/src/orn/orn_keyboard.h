#ifndef __orn_keyboard_h__
#define __orn_keyboard_h__

#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"

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