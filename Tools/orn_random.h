#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "stdbool.h"
#include "time.h"

void orn_random_init( unsigned int graine);
int orn_random_nextInt(int min, int max);

#endif