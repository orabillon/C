#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "orn_lists.h"
#include "orn_memoire.h"


/**
* Retourne une Liste vide
* @return Une nouvelle Liste
*/
List* orn_list_new(void)
{
	return NULL;
}

/**
* Teste si une Liste est vide
* @param li La Liste
* @return true si la Liste ne contient pas d'éléments, sinon false
*/
bool orn_list_isEmpty(List* li)
{
	if(li == NULL)
	{
		return true;
	}
	
	return false;
}

/**
* Retourne la longueur d'une Liste
* @param li La Liste
* @return Le nombre d'éléments de la Liste
*/
int orn_list_lenght(List* li)
{
	if(orn_list_isEmpty(li))
		return 0;

	return li->length;
}

/**
* Retourne le premier élément de la Liste
* @param li La Liste
* @return Le premier element
*/
void* orn_list_first(List* li)
{
	if(orn_list_isEmpty(li))
		exit(EXIT_FAILURE);

	return li->begin->data;
}

/**
* Retourne le dernier élément de la Liste
* @param li La Liste
* @return Le dernier element 
*/
void* orn_list_last(List* li)
{
	if(orn_list_isEmpty(li))
		exit(EXIT_FAILURE);

	return li->end->data;
}

/**
* Affiche une Liste
* @param li La Liste à parcourir
*/
void orn_list_print(List* li, char* separateur)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a afficher, la Liste est vide.\n");
		return;
	}

	Node* temp = li->begin;

	printf("[ ");
   
   while(temp != NULL)
	{
        (temp->printFunc)(temp->data);
        printf("%s",separateur);

		temp = temp->next;
	}

    printf(" ]\n");

	printf("\n");
}

/**
* Insère un élément en fin de Liste
* @param li La Liste
* @param value pointeur sur la valeur à ajouter
* @param void (*printFunc)(void*) pointeur de fonction pour l'affichage d'un element 
* @return La Liste avec son élément ajouté
*/
List* orn_list_add_back(List* li, void* value, void (*printFunc)(void*))
{
	Node* element;

	element = orn_memory_alloc(sizeof(*element),"orn_list_add_back");

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->data = value;
	element->next = NULL;
	element->previous = NULL;
	element->printFunc = printFunc;

	if(orn_list_isEmpty(li))
	{
		li = orn_memory_alloc(sizeof(*li),"orn_list_add_back");

		if(li == NULL)
		{
			fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
			exit(EXIT_FAILURE);
		}

		li->length = 0;
		li->begin = element;
		li->end = element;
	}
	else
	{
		li->end->next = element;
		element->previous = li->end;
		li->end = element;
	}

	li->length++;

	return li;
}


/**
* Insère un élément en début de Liste
* @param li La Liste
* @param value pointeur sur l'element à ajouter
* @param (*printFunc)(void*) pointeur de fonction pour l'affichage d'un element  
* @return La Liste avec son élémént ajouté
*/
List* orn_list_add_front(List* li, void* value, void (*printFunc)(void*))
{
	Node* element;

	element = orn_memory_alloc(sizeof(*element),"orn_list_add_front");

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->data = value;
	element->next = NULL;
	element->previous = NULL;
	element->printFunc = printFunc;

	if(orn_list_isEmpty(li))
	{
		li = orn_memory_alloc(sizeof(*li),"orn_list_add_front");

		if(li == NULL)
		{
			fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
			exit(EXIT_FAILURE);
		}

		li->length = 0;
		li->begin = element;
		li->end = element;
	}
	else
	{
		li->begin->previous = element;
		element->next = li->begin;
		li->begin = element;
	}

	li->length++;

	return li;
}

/**
* Retire un élément en début de Liste
* @param li La Liste
* @return La Liste moins l'élément supprimé
*/
List* orn_list_remove_front(List* li)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_new();
	}

	if(li->begin == li->end)
	{
		orn_memory_free(li->begin,sizeof(struct Node),"orn_list_remove_front : Node");
		orn_memory_free(li,sizeof(struct List),"orn_list_remove_front : Liste");
		li = NULL;

		return orn_list_new();
	}

	Node *temp = li->begin;

	li->begin = li->begin->next;
	li->begin->previous = NULL;
	temp->next = NULL;
	temp->previous = NULL;

	orn_memory_free(temp,sizeof(struct Node),"orn_list_remove_front : Node");
	temp = NULL;

	li->length--;

	return li;
}


/**
* Retire un élément en fin de Liste
* @param li La Liste
* @return La Liste moins l'élément supprimé
*/
List* orn_list_remove_back(List* li)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_new();
	}

	if(li->begin == li->end)
	{
		orn_memory_free(li->begin,sizeof(struct Node),"orn_list_remove_front : Node");
		orn_memory_free(li,sizeof(struct List),"orn_list_remove_front : Liste");
		li = NULL;

		return orn_list_new();
	}

	Node *temp = li->end;

	li->end = li->end->previous;
	li->end->next = NULL;
	temp->next = NULL;
	temp->previous = NULL;

	orn_memory_free(temp,sizeof(struct Node),"orn_list_remove_front : Node");
	temp = NULL;

	li->length--;

	return li;
}


/**
* Retire un élément de la Liste
* @param li La Liste
* @param target element a supprimer
* @return La Liste moins l'élément supprimé
*/
List* orn_list_remove_element(List* li, void* target)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_new();
	}

	Node *current = li->begin;

	while (current != NULL) {
        if (current->data == target) {
            if (current->previous != NULL)
			{
				current->previous->next = current->next;
			}
            else
			{
				li->begin = current->next;
			}
                
            if (current->next != NULL)
			{
				current->next->previous = current->previous;
			} 
            else
			{
				li->end = current->previous;
			}
                
            free(current);
            li->length--;
			
			return li;
        }
        current = current->next;
    }

	return li;
}


/**
* Nettoie complètement une Liste de ses éléments
* @param li La Liste à effacer
* @return Une nouvelle Liste (vide)
*/
List* orn_list_clear(List* li)
{
	while(!orn_list_isEmpty(li))
		li = orn_list_remove_back(li);

	return orn_list_new();
}