#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__

#include <stdbool.h>

extern int memoire_allouee;
extern bool memoire_debug;


/**
* Initialise la variable global de gestion de taille de memoire.
* Initialise mode debug a false
* A faire avant toute allocation dinamyque.
*/
void _orn_memory_init(void);

/**
* alloue une zone memoire et met a jour variable de controle 
* @param taille Taille a allouee dinamyquement
* @param szFonction Nom fonction appelante
* @return adresse memoire de la memoire allouee
*/
void* orn_memory_alloc(int const taille, char* szFonction);

/**
* libere une zone memoire et met le pointeur a null
* @param ptr adresse a libere
* @param taille taille libere
* @param szFonction Nom fonction appelante
*/
void orn_memory_free(void* ptr, int const taille, char* szFonction);

/**
* Verifie l'etat de la variable global et met un message d'erreur en cas de fuite
* A faire a la fermeture du programe
*/
void orn_memory_check(void);

/**
* Re-allou la memoiure 
* @param ptr adresse a libere
* @param old_size ancienne taille 
* @param new_size nouvelle taille 
*/
void* orn_memory_realloc (void* pptr, int old_size, int new_size);

#endif