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

int* createPredecessors(int numberOfVertex)
{
    int* predecessors = (int*)malloc(numberOfVertex * sizeof(int));
    for(int i = 0; i < numberOfVertex; ++i)
    {
        predecessors[i] = -1;
    }

    return predecessors;
}

int** createFloydAdjMatrix(int** adjacencyMatrix, int numberOfVertex)
{
    int** floydAdjMatrix = matrixCreate(numberOfVertex);

    for(int i = 0; i < numberOfVertex; ++i)
    {
        for(int j = 0; j < numberOfVertex; ++j)
        {
            if(i != j && adjacencyMatrix[i][j] == 0)
            {
                floydAdjMatrix[i][j] = __INT_MAX__;
            }
            else
            {
                floydAdjMatrix[i][j] = adjacencyMatrix[i][j];
            }
        }
    }

    return floydAdjMatrix;

    return NULL;
}

int** createFloydPredecessorsMatrix(int** adjacencyMatrix, int numberOfVertex)
{
    int** floydPredMatrix = (int**)malloc(numberOfVertex * sizeof(int*));
    if(floydPredMatrix == NULL)
    {
        printf("Memory error! Aborting...\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < numberOfVertex; ++i)
    {
        floydPredMatrix[i] = createPredecessors(numberOfVertex);

        for(int j = 0; j < numberOfVertex; ++j)
        {
            if(i != j && adjacencyMatrix[i][j] != 0)
            {
                floydPredMatrix[i][j] = i;
            }
        }
    }

    return floydPredMatrix;
}