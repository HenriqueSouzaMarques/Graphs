#include <stdio.h>
#include <stdlib.h>

#include "../Includes/graph.h"
#include "../Includes/queue.h"

#include "utils.c"

typedef enum vertexType
{
    WHITE,
    GRAY,
    BLACK
} vertexType_t;

struct graph
{
    int numberOfVertex;
    int numberOfEdges;

    int** adjacencyMatriz; 
};

graph_t* graphCreate(int numberOfVertex)
{
    if(numberOfVertex <= 0)
    {
        printf("Inform a valid number of vertex!\n");
        return NULL;
    }

    graph_t* graph = (graph_t*)malloc(sizeof(graph_t));

    if(graph == NULL)
    {
        printf("Memory error! Aborting...\n");
        exit(EXIT_FAILURE);
    }

    graph->numberOfVertex = numberOfVertex;
    graph->numberOfEdges = 0;
    graph->adjacencyMatriz = matrixCreate(numberOfVertex);

    return graph;
}

void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight, BOOL isDirected)
{
    if(weight <= 0)
    {
        printf("Insert a valid weight (positive integer!)\n");
        return;
    }

    if(vertexIsInvalid(vertexA, graph->numberOfVertex) || vertexIsInvalid(vertexB, graph->numberOfVertex))
    {
        printf("Insert a valid edge!\n");
        return;
    }
    
    graph->adjacencyMatriz[vertexA][vertexB] = weight;

    if(!isDirected)
    {
        graph->adjacencyMatriz[vertexB][vertexA] = weight; 
    }

    graph->numberOfEdges++;
}

void graphRemoveEdge(graph_t* graph, int vertexA, int vertexB, BOOL isDirected)
{
    if(vertexIsInvalid(vertexA, graph->numberOfVertex) || vertexIsInvalid(vertexB, graph->numberOfVertex))
    {
        printf("Insert a valid edge!\n");
        return;
    }

    graph->adjacencyMatriz[vertexA][vertexB] =  0;

    if(!isDirected)
    {
        graph->adjacencyMatriz[vertexB][vertexA] = 0;
    }
    
    graph->numberOfEdges--;
}


void _graphBFS(graph_t* graph, vertexType_t* visiteds, int initialVertex)
{
    queue_t* queue = createQueue();
    push(queue, initialVertex);
    visiteds[initialVertex] = GRAY;

    while(!isEmpty(queue))
    {
        int currentVertex = pop(queue);

        printf("Vertex visited by %d: ", currentVertex);

        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatriz[currentVertex][i] != 0 && visiteds[i] == WHITE)
            {
                printf("%d(%d) ", i, graph->adjacencyMatriz[currentVertex][i]);
                push(queue, i);
                visiteds[i] = GRAY;
            }
        }

        printf("\n");
        visiteds[currentVertex] = BLACK;
    }

    destroyQueue(&queue);
}

int graphBFS(graph_t* graph)
{
    vertexType_t* visiteds = (vertexType_t*)calloc(graph->numberOfVertex, sizeof(vertexType_t));

    if(visiteds == NULL)
    {
        printf("Memory error! Aborting...\n");
        exit(EXIT_FAILURE);        
    }

    int numberOfConnectedComponents = 0;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(visiteds[i] == WHITE)
        {
            numberOfConnectedComponents++;
            _graphBFS(graph, visiteds, i);
        }
    }

    free(visiteds);

    return numberOfConnectedComponents;
}

void _graphDFS(graph_t* graph, vertexType_t* visiteds, int* discovered, int* processed, int* predecessors, int* actualTime, int actualVertex)
{
    visiteds[actualVertex] = GRAY;
    discovered[actualVertex] = ++(*actualTime);

    for(int next = 0; next < graph->numberOfVertex; ++next)
    {
        if(graph->adjacencyMatriz[actualVertex][next] != 0 && visiteds[next] == WHITE)
        {
            predecessors[next] = actualVertex;
            _graphDFS(graph, visiteds, discovered, processed, predecessors, actualTime, next);
        }
    }

    visiteds[actualVertex] = BLACK;
    processed[actualVertex] = ++(*actualTime);

    printf("Vertex: %2d -- discovered at step number %2d -- processed at step number %2d -- predecessor vertex is %2d\n", actualVertex, discovered[actualVertex], processed[actualVertex], predecessors[actualVertex]);
}

int graphDFS(graph_t* graph)
{
    vertexType_t* visiteds = (vertexType_t*)calloc(graph->numberOfVertex, sizeof(vertexType_t));

    int* discovered = (int*)calloc(graph->numberOfVertex, sizeof(int));

    int* processed = (int*)calloc(graph->numberOfVertex, sizeof(int));

    int* predecessors = (int*)malloc(graph->numberOfVertex * sizeof(int));
    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        predecessors[i] = -1;
    }

    int numberOfConnectedComponents = 0;

    int actualTime = 0;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(visiteds[i] == WHITE)
        {
            numberOfConnectedComponents++;
            _graphDFS(graph, visiteds, discovered, processed, predecessors, &actualTime, i);
        }
    }
    printf("\n");

    free(visiteds);
    free(discovered);
    free(processed);
    free(predecessors);

    return numberOfConnectedComponents;
}


void graphDelete(graph_t** graph)
{
    if(graph == NULL || *graph == NULL) return;

    matrixDelete(&((*graph)->adjacencyMatriz), (*graph)->numberOfVertex);

    free(*graph);

    *graph = NULL;
}