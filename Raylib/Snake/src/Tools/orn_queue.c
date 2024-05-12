#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "orn_memoire.h"
#include "orn_queue.h"

/**
* Initialise une nouvelle queue
* @return queue noouvelle queue
*/
Queue* orn_queue_newQueue(void) 
{
   
    Queue *queue =orn_memory_alloc(sizeof(Queue),"orn_queue_newQueue");

    if (queue == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour la queue.\n");
        exit(EXIT_FAILURE);
    }

    queue->first = NULL;
    queue->last = NULL;
    queue->lenght = 0;
    return queue;
}

/**
* Teste si une queue est vide
* @param queue queue a tester
* @return true si la queue ne contient pas d'éléments, sinon false
*/
bool orn_queue_isEmpty(Queue *queue) {
    return (queue->first == NULL);
}

/**
* Ajoute un élément à la fin de la queue
* @param queue queue ou ajouter l'élément 
* @param data Pointeur vers le contenu de l'élément 
*/
void orn_queue_enqueue(Queue *queue, void *data) 
{
    Node *newNode = orn_memory_alloc(sizeof(Node),"orn_queue_enqueue");

    if (newNode == NULL) 
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le nouvel élément.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (orn_queue_isEmpty(queue)) 
    {
        queue->first = newNode;
        queue->last = newNode;
    } 
    else 
    {
        queue->last->next = newNode;
        queue->last = newNode;
    }
    queue->lenght++;
}

/**
* Supprime et retourne l'élément en tête de queue
* @param queue queue ou supprimer l'élément 
* @return data Pointeur vers le contenu de l'élément 
*/
void* orn_queue_dequeue(Queue *queue) 
{
    if (orn_queue_isEmpty(queue)) 
    {
        fprintf(stderr, "La queue est vide.\n");
        exit(EXIT_FAILURE);
    }

    void *data = queue->first->data;

    Node *temp = queue->first;
    queue->first = queue->first->next;
    
    orn_memory_free(temp, sizeof(struct Node), "orn_queue_dequeue");
    
    queue->lenght--;

    return data;
}

/**
* Retourne la taille de la queue
* @param queue queue dont on veut la taille 
* @return int taille de la liste
*/
int orn_queue_lenght(Queue *queue) {
    return queue->lenght;
}

/**
* Supprime tous les éléments de la queue
* @param queue queue a vider
*/
void orn_queue_clearQueue(Queue *queue) {
    while (!orn_queue_isEmpty(queue)) {
        orn_queue_dequeue(queue);
    }
}

/**
* Supprime la queue
* @param queue queue a supprimer et libere la mémoire
* @return int taille de la liste
*/
void orn_queue_remove(Queue *queue)
{
    orn_queue_clearQueue(queue);
    orn_memory_free(queue,sizeof(Queue),"orn_queue_remove");
}

/**
* Affiche la queue sans alteration de la queue 
* @param queue queue a afficher
* @param separateur separateur pour l'affichage
* @param void (*printFunc)(void*) pointeur de fonction pour l'affichage
*/
void orn_queue_print(Queue *queue, char* separateur,void (*printFunc)(void*))
{
    if(orn_queue_isEmpty(queue))
	{
		printf("Rien a afficher, la file est vide.\n");
		return;
	}

	Node* temp = queue->first;

	printf("[ ");
   
   while(temp != NULL)
	{
        printFunc(temp->data);
        printf("%s",separateur);

		temp = temp->next;
	}

    printf(" ]\n");

	printf("\n");
}

/**
* Retourne l'élément à l'index donné dans la queue
* @param queue queue pour la recherche
* @param index index de l'élément rechercher 
* @result *void pointeur de la donnée trouver 
*/
void* orn_queue_getAtIndex(Queue *queue, int index) {
    if (index < 0 || index >= queue->lenght) {
        fprintf(stderr, "Index hors limites.\n");
        return NULL;
    }

    Node *current = queue->first;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}