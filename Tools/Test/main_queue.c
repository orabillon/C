#include "orn_queue.h"
#include "orn_memoire.h"

// Fonction pour afficher un entier
void printInt(void* data) {
    printf("%d", *((int*)data));
}

int main() {
_orn_memory_init();
memoire_debug = true;

    Queue *queue = orn_queue_newQueue();

    int i =4;
   

    int j = 6; 

    orn_queue_enqueue(queue, &i);
    orn_queue_enqueue(queue, &j);
        
    printf("Taille de la queue: %d\n", orn_queue_lenght(queue));

    printf("Element a l'index 1 : %d \n", *((int*)orn_queue_getAtIndex(queue,1)));

    orn_queue_print(queue, "-", printInt);

    orn_queue_dequeue(queue);

    orn_queue_print(queue, "-", printInt);
    
    orn_queue_remove(queue);

    orn_memory_check();
    
    return 0;
}