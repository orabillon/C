#include <stdio.h>
#include <stdlib.h>

#include "orn_memoire.h"


int memoire_allouee;

void _orn_memory_init(){
    memoire_allouee = 0;
}

void* orn_memory_alloc(int const taille, char* szFonction){
    void* ptr = malloc(taille);

    if (ptr != NULL)
    {
        memoire_allouee += taille;
        // printf("ALLOC [%s] : Memoire totale allouee : %d \n", szFonction, memoire_allouee);
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
        //  printf("FREE [%s] : Memoire totale allouee : %d \n", szFonction, memoire_allouee);
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