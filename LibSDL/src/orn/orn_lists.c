#include <stdio.h>
#include <stdlib.h>
#include "orn_lists.h"
#include "orn_animation.h"

orn_listAnimation 	orn_list_listeAnimation_newList(void);
orn_listAnimation 	orn_list_listeAnimation_freeList(void);
bool 			orn_list_listeAnimation_is_empty(orn_listAnimation li);
void 			orn_list_listeAnimation_print(orn_listAnimation li);
int 			orn_list_listeAnimation_length(orn_listAnimation li);
orn_listAnimation 	orn_list_listeAnimation_clear(orn_listAnimation li);
orn_listAnimation 	orn_list_listeAnimation_deleteAnimation(orn_animation *animation);
orn_listAnimation 	orn_list_listeAnimation_insertAnimation(orn_animation *animation);
