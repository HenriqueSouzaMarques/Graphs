#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../Includes/queue.h"

typedef struct node node_t;

struct node
{
    element value;
    node_t* next;
};


struct queue
{
    node_t *start; node_t *end;
};

queue_t* createQueue()
{
    queue_t* list = (queue_t*)malloc(sizeof(queue_t));
    assert(list != NULL);

    list->start = NULL;
    list->end = NULL;

    return list;
}

void push(queue_t* list, element x)
{
    assert(list != NULL);

    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->value = x;
    newNode->next = NULL;

    if(isEmpty(list))
    {
        list->start = newNode;
    }
    else
    {
        list->end->next = newNode;
    }

    list->end = newNode;
}

element pop(queue_t* queue)
{
    assert(queue != NULL);

    element x = queue->start->value;

    node_t* aux = queue->start;
    
    queue->start = queue->start->next;

    free(aux);

    return x;
}

bool isEmpty(queue_t* queue)
{
    assert(queue != NULL);

    if(queue->start == NULL)
    {
        return true;
    }

    return false;
}

void printQueue(queue_t* queue)
{
    assert(queue != NULL);

    node_t* aux = queue->start;
    while(aux != NULL)
    {
        printf("%d ", aux->value);
        
        aux = aux->next;
    }
    printf("\n");
}

void destroyQueue(queue_t** queue)
{
    if(queue == NULL || *queue == NULL) return;

    node_t* aux = (*queue)->start;
    while(aux != NULL)
    {
        (*queue)->start = aux->next;
        free(aux);
        aux = (*queue)->start;
    }

    free(*queue);
}

int getSize(queue_t* queue)
{
    assert(queue != NULL);

    int size = 0;

    node_t* aux = queue->start;
    while(aux != NULL)
    {
        size++;
        aux = aux->next;
    }

    return size;
}