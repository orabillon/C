#include <stdlib.h>
#include "orn_keyboard.h"
#include "SDL.h"

const Uint8 *_orn_sdl_keystate;
int TailleTableau;

Uint8 *_orn_oldKeystate;

orn_sdlkey _orn_keymap[] = {
    // SDL_SCANCODE = QWERTY
    {"a", SDL_SCANCODE_Q},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"right", SDL_SCANCODE_RIGHT},
    {"left", SDL_SCANCODE_LEFT},
    {"up", SDL_SCANCODE_UP},
    {"down", SDL_SCANCODE_DOWN},
    {"space", SDL_SCANCODE_SPACE}};

orn_sdlkey *_key_search(const char *key)
{
    size_t num_items = sizeof(_orn_keymap) / sizeof(orn_sdlkey);
    for (size_t i = 0; i < num_items; i++)
    {
        if (strcmp(_orn_keymap[i].key, key) == 0)
        {
            return &_orn_keymap[i];
        }
    }
    return NULL;
}

void _orn_keyboard_init(void)
{
    _orn_sdl_keystate = SDL_GetKeyboardState(&TailleTableau);
    _orn_oldKeystate = malloc(TailleTableau * sizeof(Uint8));
}

void _orn_keyboard_close(void)
{
    free(_orn_oldKeystate);
}

void orn_keyboard_old(void)
{
    for (int i = 0; i < TailleTableau; i++)
    {
        _orn_oldKeystate[i] = _orn_sdl_keystate[i];
    }
}

bool orn_keyboard_isDown(const char *key)
{
    orn_sdlkey *found = _key_search(key);

    if (found)
    {
        return _orn_sdl_keystate[found->sdl_scancode];
    }

    return NULL;
}

bool orn_keyboard_KeyPressed(const char *key)
{
    orn_sdlkey *found = _key_search(key);

    if (found)
    {
        if (!_orn_oldKeystate[found->sdl_scancode])
        {
            return _orn_sdl_keystate[found->sdl_scancode];
        }
    }

    return NULL;
}