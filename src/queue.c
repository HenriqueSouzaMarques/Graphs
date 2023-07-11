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

queue_t* queueCreate()
{
    queue_t* list = (queue_t*)malloc(sizeof(queue_t));
    assert(list != NULL);

    list->start = NULL;
    list->end = NULL;

    return list;
}

void queuePush(queue_t* queue, element x, BOOL pushBeginning)
{
    assert(queue != NULL);

    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->value = x;
    newNode->next = NULL;

    if(queueIsEmpty(queue))
    {
        queue->start = newNode;
        queue->end = newNode;
    }
    else
    {
        if(pushBeginning)
        {
            newNode->next = queue->start;
            queue->start = newNode;
        }
        else
        {
            queue->end->next = newNode;
            queue->end = newNode;
        }    
    }
}

element queuePop(queue_t* queue)
{
    assert(queue != NULL);

    element x = queue->start->value;

    node_t* aux = queue->start;
    
    queue->start = queue->start->next;

    free(aux);

    return x;
}

BOOL queueIsEmpty(queue_t* queue)
{
    assert(queue != NULL);

    if(queue->start == NULL)
    {
        return TRUE;
    }

    return FALSE;
}

void queuePrint(queue_t* queue)
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

void queueDestroy(queue_t** queue)
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

int queueGetSize(queue_t* queue)
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