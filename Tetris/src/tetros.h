#ifndef __TETROS_H__
#define __TETROS_H__

/**
 * Represente un tetrominos (forme) 
 * @param *tetros tableau des formes (rotation) 
 */
typedef struct tetros
{
    int (*tabTetros)[4][4];
    
} tetros;

void test(void);

#endif