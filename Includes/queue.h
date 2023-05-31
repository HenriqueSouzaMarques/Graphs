#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int element;
typedef struct queue queue_t;

queue_t* queueCreate();

void queuePush(queue_t* queue, element x);

element queuePop(queue_t* queue);

bool queueIsEmpty(queue_t* queue);

int queueGetSize(queue_t* queue);

void queuePrint(queue_t* queue);

void queueDestroy(queue_t** queue);

#endif //QUEUE_H