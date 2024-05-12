#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void orn_random_init( unsigned int graine);
int orn_random_nextInt(int min, int max);
int orn_random_borneMaxInt(int max);
double orn_random_0_1(void);
double orn_random_nextDouble(double min, double max);
double orn_random_borneMaxDouble(double max);
int orn_random_lancerDe(int faces);

#endif