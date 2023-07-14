#ifndef __ORN_SOUND_H__
#define __ORN_SOUND_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * Structure orn_son
 * @param  *Mix_Music musique
 */
typedef struct orn_son
{
    Mix_Music *sdl_son;
} orn_son;

/**
 * Structure orn_fx
 * @param  *Mix_Music effet sonore
 */
typedef struct orn_fx
{
    Mix_Chunk *sdl_fx;
} orn_fx;

int orn_sound_init(void);

void orn_sound_close();

orn_son orn_sound_musique_new(char *path);

void orn_sound_musique_delete(orn_son *son);

void orn_sound_musique_play(orn_son *son, int nbFois);

void orn_sound_musique_pause();

void orn_sound_musique_resume();

void orn_sound_musique_stop();

void orn_sound_musique_volume(int volume);

//-----------------------------------------------------------------------

orn_fx orn_sound_fx_new(char *path);

void orn_sound_fx_delete(orn_fx *fx);

void orn_sound_fx_play(int chanel, orn_fx *fx, int nbFois);

void orn_sound_fx_pause(int chanel);

void orn_sound_fx_resume(int chanel);

void orn_sound_fx_stop(int chanel);

void orn_sound_fx_volume(int chanel, int volume);

#endif