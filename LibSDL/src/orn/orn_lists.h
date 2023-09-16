#ifndef __LISTS__H__
#define __LISTS__H__

	#include <stdbool.h>

	/* Définition d'une Liste */
	typedef struct ListElement
	{
		int value;
		struct ListElement *next;
	}ListElement, *List;

	/* Prototypes */
	List new_list(void);
	bool is_empty_list(List li);
	void print_list(List li);
	int list_length(List li);
	List push_back_list(List li, int x);
	List push_front_list(List li, int x);
	List pop_back_list(List li);
	List pop_front_list(List li);
	List clear_list(List li);

#endif