#ifndef HEAP_H
#define HEAP_H

typedef struct heap heap_t;

#define BOOL char
#define TRUE 1
#define FALSE 0

struct heap
{
    int* vertex;

    int* queue;

    int heapSize;
};

heap_t* heapCreate(int numberOfVertex, int startVertex, BOOL buildHeap);

void heapDecreaseKey(heap_t* heap, int index);

int heapPop(heap_t* heap);

int heapFind(heap_t* heap, int vertex);

BOOL heapIsEmpty(heap_t* heap);

void heapDelete(heap_t** heap);

#endif // HEAP_H