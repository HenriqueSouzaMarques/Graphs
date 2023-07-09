#include <stdio.h>
#include <stdlib.h>

#include "../Includes/heap.h"

void swapElements(int* numberA, int* numberB)
{
    int temp = *numberA;
    *numberA = *numberB;
    *numberB = temp;
}

void heapBuild(heap_t* heap)
{
   for(int i = 0; i < heap->heapSize - 1; ++i)
   {                   
        int children = i + 1;

        while(children >= 1 && heap->queue[children / 2] > heap->queue[children]) 
        { 
            swapElements(&(heap->queue[children / 2]), &(heap->queue[children])); 
            swapElements(&(heap->vertex[children / 2]), &(heap->vertex[children]));

            children /= 2;                       
        }
   }
}

heap_t* heapCreate(int numberOfVertex, int startVertex, BOOL buidHeap)
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));

    heap->queue = (int*)malloc(numberOfVertex * sizeof(int));
    heap->vertex = (int*)malloc(numberOfVertex * sizeof(int));

    heap->heapSize = numberOfVertex;

    for(int i = 0; i < numberOfVertex; ++i)
    {
        heap->vertex[i] = i;

        heap->queue[i] = __INT_MAX__;
    }

    heap->queue[startVertex] = 0;

    if(buidHeap) heapBuild(heap);

    return heap;
}

void heapMin(heap_t* heap, int parent)
{
    int children = (2 * parent) + 1;

    if(children >= heap->heapSize) return;

    if(children + 1 < heap->heapSize && heap->queue[children + 1] < heap->queue[children])
    {
        children = children + 1;
    }

    if(heap->queue[children] < heap->queue[parent])
    {
        swapElements(&(heap->queue[children]), &(heap->queue[parent]));
        swapElements(&(heap->vertex[children]), &(heap->vertex[parent]));

        heapMin(heap, children);
    }
}

int heapPop(heap_t* heap)
{
    int first = heap->vertex[0];

    swapElements(&(heap->queue[0]), &(heap->queue[heap->heapSize - 1]));
    swapElements(&(heap->vertex[0]), &(heap->vertex[heap->heapSize - 1]));

    heap->heapSize--;

    heapMin(heap, 0);

    return first;
}

int heapFind(heap_t* heap, int elem)
{
    for(int i = 0; i < heap->heapSize; ++i)
    {
        if(heap->vertex[i] == elem) return i;
    }

    return -1;
}

BOOL heapIsEmpty(heap_t* heap)
{
    return (heap->heapSize == 0);
}

void heapDelete(heap_t** heap)
{
    free((*heap)->queue);
    (*heap)->queue = NULL;

    free((*heap)->vertex);
    (*heap)->vertex = NULL;

    free((*heap));
    *heap = NULL;
}