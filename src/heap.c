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

        while(children >= 1 && heap->distances[children / 2] > heap->distances[children]) 
        { 
            swapElements(&(heap->distances[children / 2]), &(heap->distances[children])); 
            swapElements(&(heap->vertex[children / 2]), &(heap->vertex[children]));

            children /= 2;                       
        }
   }
}

heap_t* heapCreate(int numberOfVertex, int startVertex, BOOL buidHeap)
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));

    heap->distances = (int*)malloc(numberOfVertex * sizeof(int));
    heap->vertex = (int*)malloc(numberOfVertex * sizeof(int));

    heap->heapSize = numberOfVertex;

    for(int i = 0; i < numberOfVertex; ++i)
    {
        heap->vertex[i] = i;

        heap->distances[i] = __INT_MAX__;
    }

    heap->distances[startVertex] = 0;

    if(buidHeap) heapBuild(heap);

    return heap;
}

int heapPop(heap_t* heap)
{
    int first = heap->vertex[0];

    swapElements(&(heap->distances[0]), &(heap->distances[heap->heapSize - 1]));
    swapElements(&(heap->vertex[0]), &(heap->vertex[heap->heapSize - 1]));

    heap->heapSize--;

    //heapMin(heap, 0);

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


void heapMin(heap_t* heap, int parent)
{
    int children = (2 * parent) + 1;

    if(children >= heap->heapSize) return;

    if(children + 1 < heap->heapSize && heap->distances[children + 1] < heap->distances[children])
    {
        children = children + 1;
    }

    if(heap->distances[children] < heap->distances[parent])
    {
        swapElements(&(heap->distances[children]), &(heap->distances[parent]));
        swapElements(&(heap->vertex[children]), &(heap->vertex[parent]));

        heapMin(heap, children);
    }
}

BOOL heapIsEmpty(heap_t* heap)
{
    return (heap->heapSize == 0);
}

BOOL isInHeap(heap_t* heap, int vertex)
{
    for(int i = 0; i < heap->heapSize; ++i)
    {
        if(heap->vertex[i] == vertex) return TRUE;
    }

    return FALSE;
}

void heapDelete(heap_t** heap)
{
    free((*heap)->distances);
    (*heap)->distances = NULL;

    free((*heap)->vertex);
    (*heap)->vertex = NULL;

    free((*heap));
    *heap = NULL;
}