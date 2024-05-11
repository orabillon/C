#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "orn_lists.h"
#include "orn_memoire.h"


/**
* Retourne une Liste vide
* @return Une nouvelle Liste
*/
List* orn_list_newList(void)
{
	return NULL;
}

/**
* Teste si une Liste est vide
* @param li La Liste
* @return true si la Liste ne contient pas d'éléments, sinon false
*/
bool orn_list_isEmpty(List* li)
{
	if(li == NULL)
	{
		return true;
	}
	
	return false;
}

/**
* Retourne la longueur d'une Liste
* @param li La Liste
* @return Le nombre d'éléments de la Liste
*/
int orn_list_lenght(List* li)
{
	if(orn_list_isEmpty(li))
		return 0;

	return li->length;
}

/**
* Retourne le premier élément de la Liste
* @param li La Liste
* @return Le premier element
*/
void* orn_list_getFirst(List* li)
{
	if(orn_list_isEmpty(li))
		exit(EXIT_FAILURE);

	return li->begin->data;
}

/**
* Retourne le dernier élément de la Liste
* @param li La Liste
* @return Le dernier element 
*/
void* orn_list_getLast(List* li)
{
	if(orn_list_isEmpty(li))
		exit(EXIT_FAILURE);

	return li->end->data;
}

/**
* Affiche une Liste
* @param li La Liste à parcourir
* @param void (*printFunc)(void*) pointeur de fonction pour l'affichage
*/
void orn_list_print(List* li, char* separateur, void (*printFunc)(void*))
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a afficher, la Liste est vide.\n");
		return;
	}

	Node* temp = li->begin;

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
* Insère un élément en fin de Liste
* @param li La Liste
* @param value pointeur sur la valeur à ajouter
* @param void (*printFunc)(void*) pointeur de fonction pour l'affichage d'un element 
* @return La Liste avec son élément ajouté
*/
List* orn_list_addBack(List* li, void* value)
{
	Node* element;

	element = orn_memory_alloc(sizeof(*element),"orn_list_addBack");

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->data = value;
	element->next = NULL;
	element->previous = NULL;

	if(orn_list_isEmpty(li))
	{
		li = orn_memory_alloc(sizeof(*li),"orn_list_addBack");

		if(li == NULL)
		{
			fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
			exit(EXIT_FAILURE);
		}

		li->length = 0;
		li->begin = element;
		li->end = element;
	}
	else
	{
		li->end->next = element;
		element->previous = li->end;
		li->end = element;
	}

	li->length++;

	return li;
}


/**
* Insère un élément en début de Liste
* @param li La Liste
* @param value pointeur sur l'element à ajouter
* @param (*printFunc)(void*) pointeur de fonction pour l'affichage d'un element  
* @return La Liste avec son élémént ajouté
*/
List* orn_list_addFront(List* li, void* value)
{
	Node* element;

	element = orn_memory_alloc(sizeof(*element),"orn_list_addFront");

	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->data = value;
	element->next = NULL;
	element->previous = NULL;

	if(orn_list_isEmpty(li))
	{
		li = orn_memory_alloc(sizeof(*li),"orn_list_addFront");

		if(li == NULL)
		{
			fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
			exit(EXIT_FAILURE);
		}

		li->length = 0;
		li->begin = element;
		li->end = element;
	}
	else
	{
		li->begin->previous = element;
		element->next = li->begin;
		li->begin = element;
	}

	li->length++;

	return li;
}

/**
* Insère un élément dans la Liste a l'index indiquer
* @param li La Liste
* @param data pointeur sur l'element à ajouter
* @param index index ou ajouter l'element 
* @param void (*printFunc)(void*)) pointeur de fonction pour l'affichage de l'element 
* @return La Liste avec son élémént ajouté
*/
List* orn_list_insertAtIndex(List* li, int index, void *data)
{
    if (index < 0 || index > li->length)
	{
		return li;
	}
        

    if (index == 0) 
	{
        // Insérer au début de la liste
        Node *newNode = (Node*)orn_memory_alloc(sizeof(struct Node), "orn_list_insertAtIndex");
        newNode->data = data;
        newNode->previous = NULL;
        newNode->next = li->begin;

        if (li->begin != NULL)
		{
			li->begin->previous = newNode;
		}    
        else
        { 
			li->end = newNode;
		}

        li->begin = newNode;

    } 
	else if (index == li->length) 
	{
        // Insérer à la fin de la liste
        orn_list_addBack(li, data);
    } 
	else 
	{
        // Insérer à un index intermédiaire
        Node *current = li->begin;
        for (int i = 0; i < index - 1; i++) 
		{
            current = current->next;
        }

        Node *newNode = (Node*)orn_memory_alloc(sizeof(struct Node), "orn_list_insertAtIndex");
        newNode->data = data;
        newNode->previous = current;
        newNode->next = current->next;
        current->next->previous = newNode;
        current->next = newNode;
    }

    li->length++;

	return li;
}


/**
* Retire un élément en début de Liste
* @param li La Liste
* @return La Liste moins l'élément supprimé
*/
List* orn_list_removeFront(List* li)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_newList();
	}

	if(li->begin == li->end)
	{
		orn_memory_free(li->begin,sizeof(struct Node),"orn_list_removeFront : Node");
		orn_memory_free(li,sizeof(struct List),"orn_list_removeFront : Liste");
		li = NULL;

		return orn_list_newList();
	}

	Node *temp = li->begin;

	li->begin = li->begin->next;
	li->begin->previous = NULL;
	temp->next = NULL;
	temp->previous = NULL;

	orn_memory_free(temp,sizeof(struct Node),"orn_list_removeFront : Node");
	temp = NULL;

	li->length--;

	return li;
}


/**
* Retire un élément en fin de Liste
* @param li La Liste
* @return La Liste moins l'élément supprimé
*/
List* orn_list_removeBack(List* li)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_newList();
	}

	if(li->begin == li->end)
	{
		orn_memory_free(li->begin,sizeof(struct Node),"orn_list_removeBack : Node");
		orn_memory_free(li,sizeof(struct List),"orn_list_removeBack : Liste");
		li = NULL;

		return orn_list_newList();
	}

	Node *temp = li->end;

	li->end = li->end->previous;
	li->end->next = NULL;
	temp->next = NULL;
	temp->previous = NULL;

	orn_memory_free(temp,sizeof(struct Node),"orn_list_removeBack : Node");
	temp = NULL;

	li->length--;

	return li;
}


/**
* Retire un élément de la Liste
* @param li La Liste
* @param target element a supprimer
* @return La Liste moins l'élément supprimé
*/
List* orn_list_removeElement(List* li, void* target)
{
	if(orn_list_isEmpty(li))
	{
		printf("Rien a supprimer, la Liste est deja vide.\n");
		return orn_list_newList();
	}

	Node *current = li->begin;

	while (current != NULL) {
        if (current->data == target) {
            if (current->previous != NULL)
			{
				current->previous->next = current->next;
			}
            else
			{
				li->begin = current->next;
			}
                
            if (current->next != NULL)
			{
				current->next->previous = current->previous;
			} 
            else
			{
				li->end = current->previous;
			}
                
            orn_memory_free(current,sizeof(struct Node),"orn_list_removeElement");
            li->length--;
			
			return li;
        }
        current = current->next;
    }

	return li;
}

/**
* retourne l'index d'un element dans la liste
* @param li  la liste  
* @param target élément rechercher 
* @return index de l'élémént trouver ou  -1
*/
int orn_list_getIndex(List *li, void *target) {
    
	int index = 0;
    Node *current = li->begin;

    while (current != NULL) 
	{
        if (current->data == target) {
            return index;
        }
        current = current->next;
        index++;
    }

    // Si l'élément n'est pas trouvé, retourner -1
    return -1;
}

/**
* Supprime un élément a un index donner
* @param li la liste
* @param index index de l'élément a effecer
* @return la Liste
*/
List* orn_list_removeAtIndex(List *li, int index) {
    if (index < 0 || index >= li->length)
	{
		printf("Erreur : index hors des limites de la liste. Index valide : 0 - %d \n", li->length -1);
		return li;
	}

    Node *current = li->begin;

    for (int i = 0; i < index; i++) 
	{
        current = current->next;
    }

    if (current->previous != NULL)
	{
        current->previous->next = current->next;
	}
    else
	{
        li->begin = current->next;
	}
    
    if (current->next != NULL)
	{
        current->next->previous = current->previous;
	}
    else
	{
        li->end = current->previous;
	}

    orn_memory_free(current,sizeof(struct Node),"orn_list_removeAtIndex");
    li->length--;

	return li;

}


/**
* Nettoie complètement une Liste de ses éléments
* @param li La Liste à effacer
* @return Une nouvelle Liste (vide)
*/
List* orn_list_clear(List* li)
{
	while(!orn_list_isEmpty(li))
	{
		li = orn_list_removeBack(li);
	}

	return orn_list_newList();
}

/**
* Test si la liste contient un element 
* @param li La Liste à effacer
* @param data pointeur de la données a chercher 
* @return true si l'element est trouver 
*/
bool orn_list_contains(List *li, void *data) {
    
	Node *current = li->begin;

    while (current != NULL) 
	{
        if (current->data == data) {
            return true; 
        }
        current = current->next;
    }
    return false; 
}

/**
* Ajoute le contenu de la liste a Concatener a la fin de la liste de base. La liste a Concatener est ensuite liberer 
* @param liBase liste ou sera fait l'ajout
* @param liAConcatener liste qui sera ajouter et liberer
* @return true si l'element est trouver 
*/
List* orn_list_concatenate(List *liBase, List *liAConcatener) 
{
    if (liBase->end != NULL && liAConcatener->begin != NULL) 
	{
        // La queue de la première liste devient le dernier élément de la deuxième liste
        liBase->end->next = liAConcatener->begin;
        liAConcatener->begin->previous = liBase->end;
        // La queue de la deuxième liste devient la queue de la liste concaténée
        liBase->end = liAConcatener->end;
        // Mettre à jour la taille de la première liste
        liBase->length += liAConcatener->length;
        // Libérer la mémoire de la deuxième liste
        orn_memory_free(liAConcatener,sizeof(struct List), "concatenate");
    }

	return liBase;
}

/**
* Applique une fonction passer en parametre a chaque element de la liste 
* @param li liste ou on applique la fonction
* @param (*function)(void *) pointeur de fonction
* @return la liste après application de la fonction
*/
List* orn_list_map(List *li, void (*function)(void *)) 
{
    
	Node *current = li->begin;

    while (current != NULL)
	{
        function(current->data);
        current = current->next;
    }

	return li;
}

/**
* Retourne une nouvelle liste contenant les element entre deux index 
* @param li liste de base pour l'extraction
* @param start index de depart 
* @param end index de fin
* @return Nouvelle liste contenant les element extrait
*/
List* orn_list_slice(List *li, int start, int end) 
{
    if (start < 0 || end >= li->length || start > end) 
	{
        return NULL; 
    }

    List *result = orn_list_newList();
    Node *current = li->begin;

	// on se place au bonne endroit pour l'extraction
    for (int i = 0; i < start; i++) 
	{
        current = current->next;
    }

    for (int i = start; i <= end; i++) 
	{
        result = orn_list_addBack(result,current->data);
        current = current->next;
    }

    return result;
}

/**
* Retourne une nouvelle liste contenant les element filtrer
* @param li liste de base pour l'application du filtre
* @param (*predicate)(void *) filtre
* @return Nouvelle liste contenant les element extrait
*/
List* orn_list_filter(List *li, int (*predicate)(void *)) 
{
    List *result = orn_list_newList();
    Node *current = li->begin;

    while (current != NULL) 
	{
        if (predicate(current->data)) 
		{
            result = orn_list_addBack(result, current->data);
        }

        current = current->next;
    }
    return result;
}

/**
* Supprime les doublon de la liste
* @param li liste pour la suppression des doublon
* @return liste sans doublon
*/
List* orn_list_removeDuplicates(List *li)
{
    Node *current = li->begin;

    while (current != NULL) 
	{
        Node *runner = current->next;

        while (runner != NULL) 
		{
            // Comparaison des données des nœuds actuel et runner
            if (current->data == runner->data) 
			{
                // Supprimer le nœud runner
                Node *temp = runner;
                if (runner->previous != NULL)
				{
					runner->previous->next = runner->next;
				}
                else
				{
					li->begin = runner->next;
				}
                    
                if (runner->next != NULL)
				{
					runner->next->previous = runner->previous;
				}    
                else
				{
					li->end = runner->previous;
				}
                    
                runner = runner->next;

                orn_memory_free(temp,sizeof(struct Node),"orn_list_removeDuplicates");

                li->length--;
            } 
			else 
			{
                runner = runner->next;
            }
        }
        current = current->next;
    }

	return li;
}

/**
* Melange aleatoirement la liste 
* @param li liste pour le melange
* @return liste mélanger
*/
List* orn_list_shuffle(List *li) 
{
    // Initialiser le générateur de nombres aléatoires avec une graine basée sur le temps
    srand(time(NULL));

    int n = li->length;

    Node *current = li->begin;

    // Parcourir la liste et échanger chaque élément avec un élément aléatoire
    while (current != NULL) 
	{
        // Sélectionner un indice aléatoire entre 0 et n-1
        int randomIndex = rand() % n;

        // Trouver le nœud à l'indice aléatoire
        Node *randomNode = li->begin;
        for (int i = 0; i < randomIndex; i++) 
		{
            randomNode = randomNode->next;
        }

        // Échanger les données des nœuds actuel et aléatoire
        void *temp = current->data;
        current->data = randomNode->data;
        randomNode->data = temp;

        // Passer au nœud suivant
        current = current->next;
    }

	return li;
}


/**
* Fonction pour supprimer tous les éléments de la liste compris entre les indices de début et de fin donnés 
* @param li liste pour la suppression 
* @param start index de depart de la suppression
* @param end index de fin de la suppression
* @return liste apres suppression de la selection
*/
List* orn_list_removeInRange(List *li, int start, int end)
{
    if (start < 0 || end >= li->length || start > end) 
	{
        return li;
    }

    Node *current = li->begin;
    Node *startNode = NULL;
    Node *endNode = NULL;

    // Trouver le nœud de début
    for (int i = 0; i < start; i++) 
	{
        current = current->next;
    }
    startNode = current;

	current = li->begin;
    // Trouver le nœud de fin
    for (int i = 0; i < end; i++) 
	{
        current = current->next;
    }
    endNode = current;

    // Mettre à jour les pointeurs des nœuds adjacents à la plage à supprimer
    if (startNode->previous != NULL)
	{
		startNode->previous->next = endNode->next;
	}  
    else
	{
		li->begin = endNode->next;
	}
        

    if (endNode->next != NULL)
	{
		endNode->next->previous = startNode->previous;
	}
    else
	{
		li->end = startNode->previous;
	}
        

    // Libérer la mémoire des nœuds supprimés
    current = startNode;
    while (current != endNode->next) 
	{
        Node *temp = current;
        current = current->next;
        orn_memory_free(temp, sizeof(struct Node),"orn_list_removeInRange");
        li->length--;
    }

	return li;
}

/**
* Fonction pour retourner un éléments de la liste a un indices donner
* @param li liste pour la suppression 
* @param index index de l'élément rechercher
* @return void retourne le pointeur de l'element trouver ou null
*/
void* orn_list_getAtIndex(List* li, int index) {
    if (li == NULL || index < 0 || index >= li->length) {
        return NULL; // Index invalide ou liste vide
    }

    Node* current = li->begin;
    int currentIndex = 0;

    // Parcourir la liste jusqu'à l'index spécifié
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    // Vérifier si l'élément à l'index spécifié a été trouvé
    if (current != NULL && currentIndex == index) {
        return current->data;
    } else {
        return NULL; // Index hors limites
    }
}

