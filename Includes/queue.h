#ifndef QUEUE_H
#define QUEUE_H

#define BOOL char
#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct queue queue_t;

queue_t* queueCreate();

void queuePush(queue_t* queue, element x, BOOL pushBeginning);

element queuePop(queue_t* queue);

BOOL queueIsEmpty(queue_t* queue);

int queueGetSize(queue_t* queue);

void queuePrint(queue_t* queue);

void queueDestroy(queue_t** queue);

#endif //QUEUE_H