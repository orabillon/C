#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "orn_queue.h"

/**
*  Structure de base pour un élément de la queue
* @param data  Pointeur vers les données génériques
* @param next Pointeur vers le prochain élément dans la queue
*/
typedef struct Node {
    void *data;             
    struct Node *next;      
} Node;

/**
*  Structure pour la queue elle-même
* @param first Pointeur vers le premier élément dans la queue
* @param last Pointeur vers le dernier élément dans la queue
* @param lenght Taille actuelle de la queue
*/
typedef struct Queue{
    Node *first;   
    Node *last;      
    int lenght;     
} Queue;

Queue* orn_queue_newQueue(void);
bool orn_queue_isEmpty(Queue *queue);
void orn_queue_enqueue(Queue *queue, void *data);
void* orn_queue_dequeue(Queue *queue);
int orn_queue_lenght(Queue *queue);
void orn_queue_remove(Queue *queue);
void orn_queue_clearQueue(Queue *queue);
void orn_queue_print(Queue *queue, char* separateur,void (*printFunc)(void*));
void* orn_queue_getAtIndex(Queue *queue, int index);

#endif