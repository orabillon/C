#include "orn_queue.h"
#include "orn_memoire.h"

int main() {
_orn_memory_init();
memoire_debug = true;

    Queue *queue = orn_queue_newQueue();

    int i =4;
   

    int j = 6; 

    orn_queue_enqueue(queue, &i);
    orn_queue_enqueue(queue, &j);
        
    printf("Taille de la queue: %d\n", orn_queue_lenght(queue));
    
    orn_queue_remove(queue);

    orn_memory_check();
    
    return 0;
}