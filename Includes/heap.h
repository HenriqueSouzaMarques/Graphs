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

void heapMin(heap_t* heap, int parent);

int heapPop(heap_t* heap);

int heapFind(heap_t* heap, int elem);

BOOL heapIsEmpty(heap_t* heap);

BOOL isInHeap(heap_t* heap, int vertex);

void heapDelete(heap_t** heap);

#endif // HEAP_H