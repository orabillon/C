#ifndef __LISTS__H__
#define __LISTS__H__

	#include <stdbool.h>
	#include "orn_memoire.h"

	/**
	 * Structure noeud generique 
	 * @param data donne de la structure
	 * @param previous noeud precedent 
	 * @param next noeud suivant de la lise 
	 * @param fun_print pointeur de fonction pour afficher l'element
	 */
	 typedef struct Node {
		void* data;
		struct Node* previous;
		struct Node* next;
		void (*printFunc)(void*);
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


	List* orn_list_new(void);
	bool orn_list_isEmpty(List* li);
	int orn_list_lenght(List* li);
	void* orn_list_first(List* li);
	void* orn_list_last(List* li);
	void orn_list_print(List* li, char* separateur);
	List* orn_list_add_back(List* li, void* value, void (*printFunc)(void*)); 
	List* orn_list_add_front(List* li, void* value, void (*printFunc)(void*));
	List* orn_list_remove_front(List* li);
	List* orn_list_remove_back(List* li);
	List* orn_list_remove_element(List* li, void* target);
	List* orn_list_clear(List* li);

#endif