#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int element;
typedef struct queue queue_t;

queue_t* createQueue();

void push(queue_t* queue, element x);

element pop(queue_t* queue);

bool isEmpty(queue_t* queue);

int getSize(queue_t* queue);

void printQueue(queue_t* queue);

void destroyQueue(queue_t** queue);

#endif //QUEUE_H