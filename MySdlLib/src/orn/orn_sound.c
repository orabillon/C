#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "orn_sound.h"

/**
 * Initialise le module audio SDL_MIXER
 *
 * @return -1 en cas d'échec sinon 1
 * */
int _orn_sound_init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s\n", Mix_GetError());
        return -1;
    }
    // nombre de son jouable en meme temps
    Mix_AllocateChannels(10);
    return 1;
}

/**
 * Cloture le module audio SDL_MIXER
 */
void _orn_sound_close()
{
    Mix_CloseAudio();
}

/**
 * Charge une musique
 * @param path Chemin du fichier son a charger
 * @return orn_son representant le son charger
 * */
orn_son orn_sound_musique_new(char *path)
{
    orn_son son = {NULL};

    son.sdl_son = Mix_LoadMUS(path);

    if (son.sdl_son == NULL)
    {
        printf("Unable to load %s Error %s\n", path, Mix_GetError());
    }

    return son;
}

/**
 * suprimme une musique et libere la memoire associer
 * @param son fichier a suprimmer
 * */
void orn_sound_musique_delete(orn_son *son)
{

    Mix_FreeMusic(son->sdl_son);
}

/**
 * joue une musique
 * @param son Son a lire
 * @param nbFois Nombre de fois ou le son doit etre jouer [ 0 : 1 fois  -1 pour jouer sans interruption ]
 * */
void orn_sound_musique_play(orn_son *son, int nbFois)
{
    Mix_PlayMusic(son->sdl_son, nbFois);
}

/**
 * met en pause une musique
 * */
void orn_sound_musique_pause()
{
    Mix_PauseMusic();
}

/**
 * reprend une musique au niveau de la pause
 * */
void orn_sound_musique_resume()
{
    Mix_ResumeMusic();
}

/**
 * interrompt une musique
 * */
void orn_sound_musique_stop()
{
    Mix_HaltMusic();
}

/**
 * Modifier le volume d'une musique
 * @param volume Valeur de 0 a 128 [MIX_MAX_VOLUME = 128]
 * */
void orn_sound_musique_volume(int volume)
{
    Mix_VolumeMusic(volume);
}

//-----------------------------------------------------------------------

/**
 * Charge un son
 * @param path Chemin du fichier fx a charger
 * @return orn_fx representant le fx charger
 * */
orn_fx orn_sound_fx_new(char *path)
{

    orn_fx fx = {NULL};

    fx.sdl_fx = Mix_LoadWAV(path);

    if (fx.sdl_fx == NULL)
    {
        printf("Unable to load %s Error %s\n", path, Mix_GetError());
    }

    return fx;
}

/**
 * Suprimme un son et libere la memoire
 * @param fx son a liberer
 * */
void orn_sound_fx_delete(orn_fx *fx)
{

    Mix_FreeChunk(fx->sdl_fx);
}

/**
 * Lance la lecture d'un son
 * @param chanel numero du chanel ou lire le son [-1 prend le premier chanel disponible]
 * @param fx son a lancer
 * @param nbFois nombre de fois a jouer [0: 1 fois, 1: 2 fois ... -1 en boucle]
 * */
void orn_sound_fx_play(int chanel, orn_fx *fx, int nbFois)
{
    Mix_PlayChannel(chanel, fx->sdl_fx, nbFois);
}

/**
 * Met en pause un son
 * @param chanel Chanel a mettre en pause [-1 pour tous]
 * */
void orn_sound_fx_pause(int chanel)
{
    Mix_Pause(chanel);
}

/**
 * reprend la lecture d'un son en pause
 * @param chanel Chanel reprendre [-1 pour tous]
 * */
void orn_sound_fx_resume(int chanel)
{
    Mix_Resume(chanel);
}

/**
 * arrete la lecture d'un son
 * @param chanel Chanel a interrompre [-1 pour tous]
 * */
void orn_sound_fx_stop(int chanel)
{
    Mix_HaltChannel(chanel);
}

/**
 * Modifie le son d'un chanel
 * @param chanel numero du chanel a réglé [-1 modifie tous les chanel]
 * @param volume niveau du volume de 1 a 128. [-1 retourne le volume courrant]
 * */
void orn_sound_fx_volume(int chanel, int volume)
{
    Mix_Volume(chanel, volume);
}
