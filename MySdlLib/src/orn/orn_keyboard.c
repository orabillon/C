#include <stdlib.h>
#include "orn_keyboard.h"
#include "SDL.h"
#include "orn_memoire.h"

const Uint8 *_orn_sdl_keystate;
int TailleTableau;

Uint8 *_orn_oldKeystate;

/**
 * Structure de mappage du clavier
 * Attention ScanCode clavier en qwerty
 */
orn_sdlkey _orn_keymap[] = {
    // SDL_SCANCODE = QWERTY
    {"a", SDL_SCANCODE_Q},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"e", SDL_SCANCODE_E},
    {"f", SDL_SCANCODE_F},
    {"g", SDL_SCANCODE_G},
    {"h", SDL_SCANCODE_H},
    {"i", SDL_SCANCODE_I},
    {"j", SDL_SCANCODE_J},
    {"k", SDL_SCANCODE_K},
    {"l", SDL_SCANCODE_L},
    {"m", SDL_SCANCODE_SEMICOLON},
    {"n", SDL_SCANCODE_N},
    {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P},
    {"q", SDL_SCANCODE_A},
    {"r", SDL_SCANCODE_R},
    {"s", SDL_SCANCODE_S},
    {"t", SDL_SCANCODE_T},
    {"u", SDL_SCANCODE_U},
    {"v", SDL_SCANCODE_V},
    {"w", SDL_SCANCODE_Z},
    {"x", SDL_SCANCODE_X},
    {"y", SDL_SCANCODE_Y},
    {"z", SDL_SCANCODE_W},

    {"right", SDL_SCANCODE_RIGHT},
    {"left", SDL_SCANCODE_LEFT},
    {"up", SDL_SCANCODE_UP},
    {"down", SDL_SCANCODE_DOWN},

    {"space", SDL_SCANCODE_SPACE},
    {"enter", SDL_SCANCODE_RETURN},
    {"escape", SDL_SCANCODE_ESCAPE},
    {"tab", SDL_SCANCODE_TAB},
    {"back", SDL_SCANCODE_BACKSPACE},
    {"alt", SDL_SCANCODE_LALT},
    {"altGr", SDL_SCANCODE_RALT},
    {"lctrl", SDL_SCANCODE_LCTRL},
    {"rctrl", SDL_SCANCODE_RCTRL},
    {"lshift", SDL_SCANCODE_LSHIFT},
    {"rshift", SDL_SCANCODE_RSHIFT},

    {"F1", SDL_SCANCODE_F1},
    {"F2", SDL_SCANCODE_F2},
    {"F3", SDL_SCANCODE_F3},
    {"F4", SDL_SCANCODE_F4},
    {"F5", SDL_SCANCODE_F5},
    {"F6", SDL_SCANCODE_F6},
    {"F7", SDL_SCANCODE_F7},
    {"F8", SDL_SCANCODE_F8},
    {"F9", SDL_SCANCODE_F9},
    {"F10", SDL_SCANCODE_F10},
    {"F11", SDL_SCANCODE_F11},
    {"F12", SDL_SCANCODE_F12},

    {"1", SDL_SCANCODE_1},
    {"2", SDL_SCANCODE_2},
    {"3", SDL_SCANCODE_3},
    {"4", SDL_SCANCODE_4},
    {"5", SDL_SCANCODE_5},
    {"6", SDL_SCANCODE_6},
    {"7", SDL_SCANCODE_7},
    {"8", SDL_SCANCODE_8},
    {"9", SDL_SCANCODE_9},
    {"0", SDL_SCANCODE_0},
    {"KP1", SDL_SCANCODE_KP_1},
    {"KP2", SDL_SCANCODE_KP_2},
    {"KP3", SDL_SCANCODE_KP_3},
    {"KP4", SDL_SCANCODE_KP_4},
    {"KP5", SDL_SCANCODE_KP_5},
    {"KP6", SDL_SCANCODE_KP_6},
    {"KP7", SDL_SCANCODE_KP_7},
    {"KP8", SDL_SCANCODE_KP_8},
    {"KP9", SDL_SCANCODE_KP_9},
    {"KP0", SDL_SCANCODE_KP_0}};

/**
 * recherche la touche dans le tableau de mappage
 * @param *key touche rechercher
 * @return retourne un orn_sdlkey ou null si pas trouvé
 */
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

/**
 * initialise un objet interne pour la gestion du clavier
 */
void _orn_keyboard_init(void)
{
    _orn_sdl_keystate = SDL_GetKeyboardState(&TailleTableau);
    // _orn_oldKeystate = malloc(TailleTableau * sizeof(Uint8));
    _orn_oldKeystate = orn_memory_alloc(TailleTableau * sizeof(Uint8), "_orn_keyboard_init");
}

void _orn_keyboard_close(void)
{
    //free(_orn_oldKeystate);
    orn_memory_free(_orn_oldKeystate,TailleTableau * sizeof(Uint8), "_orn_keyboard_close");
}

/**
 * Sauvegarde l'etat precedent du tableau
 */
void orn_keyboard_old(void)
{
    for (int i = 0; i < TailleTableau; i++)
    {
        _orn_oldKeystate[i] = _orn_sdl_keystate[i];
    }
}

/**
 * Recherche dans le orn_keystate si la touche en parametre est appuyer
 * évenement continu
 * @param *key touche a chercher
 */
bool orn_keyboard_isDown(const char *key)
{
    orn_sdlkey *found = _key_search(key);

    if (found)
    {
        return _orn_sdl_keystate[found->sdl_scancode];
    }

    return NULL;
}

/**
 * Recherche dans le orn_keystate si la touche en parametre a été presser
 * évenement unique
 * @param *key touche a chercher
 */
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