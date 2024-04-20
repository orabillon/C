#ifndef __LISTS__H__
#define __LISTS__H__

	#include <stdbool.h>

	/**
	* Pointeur de fonction 
	*/
	typedef void (*fun_print)(void* ptr);

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
		fun_print print;
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



#endif