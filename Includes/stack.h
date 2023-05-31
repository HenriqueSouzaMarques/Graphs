#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stack stack_t;

stack_t* stackCreate();

void stackPush(stack_t* stack, int x);

int stackPop(stack_t* stack);

bool stackIsElem(stack_t* stack, int x);

bool stackIsEmpty(stack_t* stack);

int stackGetSize(stack_t* stack);

void stackPrint(stack_t* stack);

void stackDestroy(stack_t** stack);

#endif //STACK_H