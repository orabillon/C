#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "orn_memoire.h"



int memoire_allouee;
bool memoire_debug;

void _orn_memory_init(){
    memoire_allouee = 0;
    memoire_debug = false;
}

void* orn_memory_alloc(int const taille, char* szFonction){
    void* ptr = malloc(taille);

    if (ptr != NULL)
    {
        memoire_allouee += taille;

        if (memoire_debug)
        {
            printf("ALLOC [%s] : Memoire allouee : %d  -  Memoire totale allouee : %d \n", szFonction, taille, memoire_allouee);
        }
        
    }
    else
    {
        printf("Echec allocation dinamique.");
    }

    return ptr;
}

void orn_memory_free(void* ptr, int const taille, char* szFonction){
    if (ptr != NULL){
        free(ptr);
        memoire_allouee -= taille;

        if (memoire_debug)
        {
           printf("FREE [%s] : Memoire libere : %d  - Memoire totale allouee : %d \n", szFonction, taille, memoire_allouee);
        }
         
    }
}


void orn_memory_check(){
    if (memoire_allouee != 0){
        printf("Attention : il y a une fuite memoire. \n %d octets non libere. \n",memoire_allouee);
    }
    printf("Check memory OK !\n");
}

void*orn_memory_realloc (void* pptr, int old_size, int new_size)
{
  void* ptr = realloc (pptr, new_size);
  if (ptr == NULL)
    {
       printf("Echec allocation dinamique.");
       return NULL;
    }
 
  memoire_allouee += (new_size - old_size);
  return ptr;
}