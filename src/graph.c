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

    BOOL isDirected;

    int** adjacencyMatriz; 
};

graph_t* graphCreate(int numberOfVertex, BOOL isDirected)
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
    graph->isDirected = isDirected;
    graph->numberOfEdges = 0;
    graph->adjacencyMatriz = matrixCreate(numberOfVertex);

    return graph;
}

BOOL getIsDirected(graph_t* graph)
{
    if(graph != NULL) return graph->isDirected;

    return FALSE;
}

void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight)
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

    if(!graph->isDirected)
    {
        graph->adjacencyMatriz[vertexB][vertexA] = weight; 
    }

    graph->numberOfEdges++;
}

void graphRemoveEdge(graph_t* graph, int vertexA, int vertexB)
{
    if(vertexIsInvalid(vertexA, graph->numberOfVertex) || vertexIsInvalid(vertexB, graph->numberOfVertex))
    {
        printf("Insert a valid edge!\n");
        return;
    }

    graph->adjacencyMatriz[vertexA][vertexB] =  0;

    if(!graph->isDirected)
    {
        graph->adjacencyMatriz[vertexB][vertexA] = 0;
    }
    
    graph->numberOfEdges--;
}


void _graphBFS(graph_t* graph, vertexType_t* visiteds, int initialVertex, BOOL print)
{
    queue_t* queue = createQueue();
    push(queue, initialVertex);
    visiteds[initialVertex] = GRAY;

    while(!isEmpty(queue))
    {
        int currentVertex = pop(queue);

        if(print)
        {
            printf("Vertex visited by %d: ", currentVertex);
        }

        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatriz[currentVertex][i] != 0 && visiteds[i] == WHITE)
            {
                if(print)
                {
                    printf("%d(%d) ", i, graph->adjacencyMatriz[currentVertex][i]); 
                }

                push(queue, i);
                visiteds[i] = GRAY;
            }
        }

        if(print)
        {
            printf("\n"); 
        }

        visiteds[currentVertex] = BLACK;
    }

    destroyQueue(&queue);
}

int graphBFS(graph_t* graph, BOOL print)
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
            _graphBFS(graph, visiteds, i, print);
        }
    }

    free(visiteds);

    return numberOfConnectedComponents;
}

void _graphDFS(graph_t* graph, vertexType_t* visiteds, int* discovered, int* processed, int* predecessors, int* actualTime, int actualVertex, BOOL print)
{
    visiteds[actualVertex] = GRAY;
    discovered[actualVertex] = ++(*actualTime);

    for(int next = 0; next < graph->numberOfVertex; ++next)
    {
        if(graph->adjacencyMatriz[actualVertex][next] != 0 && visiteds[next] == WHITE)
        {
            predecessors[next] = actualVertex;
            _graphDFS(graph, visiteds, discovered, processed, predecessors, actualTime, next, print);
        }
    }

    visiteds[actualVertex] = BLACK;
    processed[actualVertex] = ++(*actualTime);

    if(print)
    {
        printf("Vertex: %2d -- discovered at step number %2d -- processed at step number %2d -- predecessor vertex is %2d\n", actualVertex, discovered[actualVertex], processed[actualVertex], predecessors[actualVertex]);
    }
}

int graphDFS(graph_t* graph, BOOL print)
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
            _graphDFS(graph, visiteds, discovered, processed, predecessors, &actualTime, i, print);
        }
    }

    if(print)
    {
        printf("\n");
    }
    
    free(visiteds);
    free(discovered);
    free(processed);
    free(predecessors);

    return numberOfConnectedComponents;
}

int vertexDegree(graph_t* graph, int vertex)
{
    int vertexDegree = 0;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(graph->adjacencyMatriz[vertex][i] != 0)
        {
                vertexDegree++;
        }
    } 

    return vertexDegree;  
}

void copyAdjancencyMatrix(graph_t* copy, graph_t* source)
{
    for(int i = 0; i < copy->numberOfVertex; ++i)
    {
        for(int j = 0; j < copy->numberOfVertex; ++j)
        {
            copy->adjacencyMatriz[i][j] = source->adjacencyMatriz[i][j];
        }
    }
}

graph_t* copyGraph(graph_t* graph)
{
    graph_t* copy = graphCreate(graph->numberOfVertex, graph->isDirected);

    copy->numberOfEdges = graph->numberOfEdges;

    copyAdjancencyMatrix(copy, graph);

    return copy;
}

BOOL graphNotEulerian(graph_t* graph)
{
    int numberOfConnectedComponents = graphBFS(graph, FALSE);

    if(numberOfConnectedComponents != 1) return TRUE;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        int currentVertexDegree = vertexDegree(graph, i);

        if(currentVertexDegree % 2 != 0) return TRUE;
    }

    return FALSE;
}

BOOL isBridge(graph_t* graph, int vertexA, int vertexB)
{

    int connectedComponentsBefore = graphBFS(graph, FALSE);

    graphRemoveEdge(graph, vertexA, vertexB);

    int connectedComponentsAfter = graphBFS(graph, FALSE);

    if(connectedComponentsAfter > connectedComponentsBefore)
    {
        graphAddEdge(graph, vertexA, vertexB, 1);

        return TRUE;
    }

    return FALSE;
}

void fleuryAlgorithm(graph_t* graph, int currentVertex)
{
    if(graph->numberOfEdges == 0) return;

    int currentVertexDegree = vertexDegree(graph, currentVertex);

    if(currentVertexDegree == 1)
    {
        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatriz[currentVertex][i] != 0)
            {
                printf(" -> %d", i);

                graphRemoveEdge(graph, currentVertex, i);

                fleuryAlgorithm(graph, i);
            }
        }
    }
    else
    {
        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatriz[currentVertex][i] != 0 && !isBridge(graph, currentVertex, i))
            {
                printf(" -> %d", i);

                fleuryAlgorithm(graph, i);
            }
        }
    }   
}

void graphEulerianCircuit(graph_t* graph, int startVertex)
{
    if(vertexIsInvalid(startVertex, graph->numberOfVertex))
    {
        printf("Insert a valid vertex!\n");
        return;
    }

    graph_t* copy = copyGraph(graph);

    printf("PATH: %d", startVertex);
    fleuryAlgorithm(copy, startVertex);
    printf("\n");

    graphDelete(&copy);
}

void graphDelete(graph_t** graph)
{
    if(graph == NULL || *graph == NULL) return;

    matrixDelete(&((*graph)->adjacencyMatriz), (*graph)->numberOfVertex);

    free(*graph);

    *graph = NULL;
}