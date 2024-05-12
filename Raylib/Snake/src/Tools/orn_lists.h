#ifndef __LISTS__H__
#define __LISTS__H__

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <time.h>
	#include "orn_lists.h"
	#include "orn_memoire.h"

	/**
	 * Structure noeud generique 
	 * @param data donne de la structure
	 * @param previous noeud precedent 
	 * @param next noeud suivant de la lise 
	 */
	 typedef struct Node {
		void* data;
		struct Node* previous;
		struct Node* next;
	} Node;

	/**
	 * Structure Liste generique
	 * @param length Taille de la liste
	 * @param begin Premier noeud de la liste
	 * @param end Dernier noeud de la liste
	 */
	 typedef struct List {
		int length;
		struct Node* begin;
		struct Node* end;
	} List;


	List* orn_list_newList(void);

	bool orn_list_isEmpty(List* li);
	int orn_list_lenght(List* li);
	void* orn_list_getFirst(List* li);
	void* orn_list_getLast(List* li);
	void orn_list_print(List* li, char* separateur,void (*printFunc)(void*));
	void* orn_list_getAtIndex(List* li, int index);

	List* orn_list_addBack(List* li, void* value); 
	List* orn_list_addFront(List* li, void* value);
	List* orn_list_insertAtIndex(List* li, int index, void *data);

	List* orn_list_removeFront(List* li);
	List* orn_list_removeBack(List* li);
	List* orn_list_removeElement(List* li, void* target);
	int orn_list_getIndex(List *li, void *target);
	List* orn_list_removeAtIndex(List *list, int index); 
	List* orn_list_clear(List* li);
	List* orn_list_removeDuplicates(List *li);
	List* orn_list_removeInRange(List *li, int start, int end);

	bool orn_list_contains(List *li, void *data);
	List* orn_list_concatenate(List *liBase, List *liAConcatener);
	List* orn_list_map(List *li, void (*function)(void *)); 
	List* orn_list_slice(List *li, int start, int end);
	List* orn_list_filter(List *li, int (*predicate)(void *)); 
	List* orn_list_shuffle(List *li);

#endif