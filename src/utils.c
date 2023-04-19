#include <stdio.h>
#include <stdlib.h>

#include "../Includes/graph.h"

BOOL vertexIsInvalid(int vertexA, int numberOfVertex)
{
    if(vertexA < 0 || vertexA >= numberOfVertex) return TRUE;

    return FALSE;
}

int** matrixCreate(int numberOfVertex)
{
    int** matriz = (int**)malloc(numberOfVertex * sizeof(int*));
    if(matriz == NULL)
    {
        printf("Memory error! Aborting...\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < numberOfVertex; ++i)
    {
        matriz[i] = (int*)calloc(numberOfVertex, sizeof(int));

        if(matriz[i] == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free(matriz[i]);
                matriz[i] = NULL;
            }

            free(matriz);
            printf("Memory error! Aborting...\n");
            exit(EXIT_FAILURE);
        }
    }

    return matriz;
}

void matrixDelete(int*** matrix, int numberOfVertex)
{
    for(int i = 0; i < numberOfVertex; ++i)
    {
        free((*matrix)[i]);
    }

    free(*matrix);

    *matrix = NULL;
}