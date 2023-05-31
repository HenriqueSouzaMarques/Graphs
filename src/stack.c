#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../Includes/stack.h"

typedef struct node node_t;

struct node
{
    int value;
    node_t* next;
};


struct stack
{
    node_t *start; node_t *end;
};

stack_t* stackCreate()
{
    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    assert(stack != NULL);

    stack->start = NULL;
    stack->end = NULL;

    return stack;
}

void stackPush(stack_t* stack, int x)
{
    assert(stack != NULL);

    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    assert(newNode != NULL);

    newNode->value = x;
    newNode->next = NULL;

    if(stackIsEmpty(stack))
    {
        stack->start = newNode;
    }
    else
    {
        stack->end->next = newNode;
    }

    stack->end = newNode;
}

int stackTop(stack_t* stack)
{
    assert(stack != NULL);

    if(stackIsEmpty(stack)) return -1;

    return stack->end->value;
}

int stackPop(stack_t* stack)
{
    int x = stackTop(stack);

    int size = stackGetSize(stack);

    node_t* aux = stack->start;
    node_t* ant = NULL;

    x = stack->end->value;

    if(size == 1)
    {
        stack->start = stack->start->next;

        free(aux);
    }
    else
    {
        while(aux != stack->end)
        {
            ant = aux;
            aux = aux->next;
        }

        free(aux);
        stack->end = ant;
        stack->end->next = NULL;
    }

    return x;
}

bool stackIsEmpty(stack_t* stack)
{
    assert(stack != NULL);

    if(stack->start == NULL)
    {
        return true;
    }

    return false;
}

bool stackIsElem(stack_t* stack, int x)
{
    assert(stack != NULL);

    node_t* start = stack->start;

    while (start != NULL)
    {
        if(start->value == x) return true;

        start = start->next;
    }

    return false;
}

void stackPrint(stack_t* stack)
{
    assert(stack != NULL);

    node_t* start = stack->start;

    while (start != NULL)
    {
        printf("%d ", start->value);

        start = start->next;
    }

    printf("\n");
}

void stackDestroy(stack_t** stack)
{
    if(stack == NULL || *stack == NULL) return;

    node_t* aux = (*stack)->start;
    while(aux != NULL)
    {
        (*stack)->start = aux->next;
        free(aux);
        aux = (*stack)->start;
    }

    free(*stack);
}

int stackGetSize(stack_t* stack)
{
    assert(stack != NULL);

    int size = 0;

    node_t* aux = stack->start;
    while(aux != NULL)
    {
        size++;
        aux = aux->next;
    }

    return size;
}