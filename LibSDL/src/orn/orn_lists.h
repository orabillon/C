#ifndef __LISTS__H__
#define __LISTS__H__

	#include <stdbool.h>
	#include "orn_animation.h"

	/**
 	* Structure element liste animation
 	*/
	typedef struct ListAnimation
	{
		orn_animation *animation;
		struct ListAnimation *next;
	}ListAnimation;

	ListAnimation new_listAnimation(void);
	bool is_empty_listAnimation(ListAnimation li);
	void print_listAnimation(ListAnimation li);
	int listAnimation_length(ListAnimation li);
	ListAnimation clear_listAnimation(ListAnimation li);
	ListAnimation deleteAnimation(orn_animation *animation);
	ListAnimation insertAnimation(orn_animation *animation);

#endif