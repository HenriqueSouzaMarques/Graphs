#include <stdio.h>
#include <stdlib.h>

#include "../Includes/graph.h"

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

    int** adjacencyMatrix; 
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
    graph->adjacencyMatrix = matrixCreate(numberOfVertex);

    return graph;
}

BOOL getIsDirected(graph_t* graph)
{
    if(graph != NULL) return graph->isDirected;

    return FALSE;
}

void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight)
{
    if(weight == 0)
    {
        printf("Insert a valid weight (it can not be 0!)\n");
        return;
    }

    if(vertexIsInvalid(vertexA, graph->numberOfVertex) || vertexIsInvalid(vertexB, graph->numberOfVertex))
    {
        printf("Insert a valid edge!\n");
        return;
    }
    
    graph->adjacencyMatrix[vertexA][vertexB] = weight;

    if(!graph->isDirected)
    {
        graph->adjacencyMatrix[vertexB][vertexA] = weight; 
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

    graph->adjacencyMatrix[vertexA][vertexB] =  0;

    if(!graph->isDirected)
    {
        graph->adjacencyMatrix[vertexB][vertexA] = 0;
    }
    
    graph->numberOfEdges--;
}


void _graphBFS(graph_t* graph, vertexType_t* visiteds, int initialVertex, BOOL print)
{
    queue_t* queue = queueCreate();
    queuePush(queue, initialVertex);
    visiteds[initialVertex] = GRAY;

    while(!queueIsEmpty(queue))
    {
        int currentVertex = queuePop(queue);

        if(print)
        {
            printf("Vertex visited by %d: ", currentVertex);
        }

        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatrix[currentVertex][i] != 0 && visiteds[i] == WHITE)
            {
                if(print)
                {
                    printf("%d(%d) ", i, graph->adjacencyMatrix[currentVertex][i]); 
                }

                queuePush(queue, i);
                visiteds[i] = GRAY;
            }
        }

        if(print)
        {
            printf("\n"); 
        }

        visiteds[currentVertex] = BLACK;
    }

    queueDestroy(&queue);
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
        if(graph->adjacencyMatrix[actualVertex][next] != 0 && visiteds[next] == WHITE)
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

    int* predecessors = createPredecessors(graph->numberOfVertex);

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

int findMinLow(graph_t* graph, int* low, int** treeEdges, int currentVertex)
{
    int min = __INT_MAX__;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(treeEdges[currentVertex][i] && low[i] < min)
        {
            min = low[i];
        }
    }

    return min;
}

int findMinDisc(graph_t* graph, stack_t* stack, int* low, int** treeEdges, int* discovered, int currentVertex)
{
    int min = __INT_MAX__;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(graph->adjacencyMatrix[currentVertex][i] != 0 && treeEdges[currentVertex][i] == 0 && stackIsElem(stack, i))
        {
            if(discovered[i] < min)
            {
                min = discovered[i];
            }
        }
    }

    return min;
}

void updateLow(graph_t* graph, stack_t* stack, int* low, int** treeEdges, int* discovered, int currentVertex)
{
    int minLow = findMinLow(graph, low, treeEdges, currentVertex);

    int minDisc = findMinDisc(graph, stack, low, treeEdges, discovered, currentVertex);

    if(discovered[currentVertex] <= minLow && discovered[currentVertex] <= minDisc)
    {
        low[currentVertex] = discovered[currentVertex];
    }
    else if(minLow <= discovered[currentVertex] && minLow <= minDisc)
    {
        low[currentVertex] = minLow;
    }
    else if(minDisc <= discovered[currentVertex] && minDisc <= minLow)
    {
        low[currentVertex] = minDisc;
    }
}

void tarjanDFS(graph_t* graph, stack_t* stack, int* low, vertexType_t* visiteds, int** treeEdges, int* discovered, int currentVertex, int* numberOfSCC, int* actualTime)
{
    stackPush(stack, currentVertex);

    visiteds[currentVertex] = GRAY;
    discovered[currentVertex] = ++(*actualTime);
    low[currentVertex] = discovered[currentVertex];

    for(int next = 0; next < graph->numberOfVertex; ++next)
    {
        if(graph->adjacencyMatrix[currentVertex][next] != 0)
        {
            if(visiteds[next] == WHITE)
            {
                treeEdges[currentVertex][next] = 1;

                tarjanDFS(graph, stack, low, visiteds, treeEdges, discovered, next, numberOfSCC, actualTime);
            }
        }
    }

    visiteds[currentVertex] = BLACK;

    updateLow(graph, stack, low, treeEdges, discovered, currentVertex);

    if(low[currentVertex] == discovered[currentVertex])
    {
        (*numberOfSCC)++;

        int vertexInSCC = 0;

        printf("Component %d : ", (*numberOfSCC));
        do
        {
            vertexInSCC = stackPop(stack);

            printf("%d ", vertexInSCC);
            
        } while (vertexInSCC != currentVertex);
        
        printf("\n");
    }
}

int tarjanAlgorithm(graph_t* graph)
{
    vertexType_t* visiteds = (vertexType_t*)calloc(graph->numberOfVertex, sizeof(vertexType_t));

    int* discovered = (int*)calloc(graph->numberOfVertex, sizeof(int));
    int* low = (int*)calloc(graph->numberOfVertex, sizeof(int));

    int** treeEdges = matrixCreate(graph->numberOfVertex);

    stack_t* stack = stackCreate();

    int numberOfSCC = 0;
    int actualTime = 0;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(visiteds[i] == WHITE)
        {
            tarjanDFS(graph, stack, low, visiteds, treeEdges, discovered, i, &numberOfSCC, &actualTime);
        }
    }

    free(visiteds);

    free(discovered);
    free(low);

    matrixDelete(&treeEdges, graph->numberOfVertex);
    
    stackDestroy(&stack);

    return numberOfSCC;
}


int vertexDegree(graph_t* graph, int vertex)
{
    int vertexDegree = 0;

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(graph->adjacencyMatrix[vertex][i] != 0)
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
            copy->adjacencyMatrix[i][j] = source->adjacencyMatrix[i][j];
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
            if(graph->adjacencyMatrix[currentVertex][i] != 0)
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
            if(graph->adjacencyMatrix[currentVertex][i] != 0 && !isBridge(graph, currentVertex, i))
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

void swap(int* numberA, int* numberB)
{
    int temp = *numberA;
    *numberA = *numberB;
    *numberB = temp;
}

void bubbleSort(int* vertex, int* degrees, int n)
{
    for(int i = 0; i < n - 1; ++i)
    {
        for(int j = 0; j < n - i - 1; ++j)
        {
            if(degrees[j] < degrees[j + 1])
            {
                swap(&degrees[j], &degrees[j + 1]);
                swap(&vertex[j], &vertex[j + 1]);
            }
        }
    }
}

int* orderVertex(graph_t* graph)
{
    int* vertex = (int*)malloc(graph->numberOfVertex * sizeof(int));
    int* degrees = (int*)malloc(graph->numberOfVertex * sizeof(int));

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        vertex[i] = i;

        degrees[i] = vertexDegree(graph, i); 
    }

    bubbleSort(vertex, degrees, graph->numberOfVertex);

    free(degrees);

    return vertex;
}

BOOL graphNotColoredYet(int* colors, int numberOfVertex)
{
    for(int i = 0; i < numberOfVertex; ++i)
    {
        if(colors[i] == 0) return TRUE;
    }

    return FALSE;
}

BOOL adjacentsColored(graph_t* graph, int* vertexOrderedByDegree, int* colors, int actualVertex, int actualColor)
{
    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(graph->adjacencyMatrix[vertexOrderedByDegree[actualVertex]][i] != 0)
        {
            if(colors[i] == actualColor) return TRUE;
        }
    }

    return FALSE;
}

int welshPowell(graph_t* graph, int* vertexOrderedByDegree, int* colors)
{
    int actualColor = 0;

    while(graphNotColoredYet(colors, graph->numberOfVertex))
    {
        actualColor++;

        for(int j = 0; j < graph->numberOfVertex; ++j)
        {
            if(colors[vertexOrderedByDegree[j]] != 0) continue;

            if(!adjacentsColored(graph, vertexOrderedByDegree, colors, j, actualColor))
            {
                colors[vertexOrderedByDegree[j]] = actualColor;
            }
        }
    }

    return actualColor;
}

void printColors(int* colors, int numberOfDifferentColors, int n)
{
    printf("Chromatic number: %d\n\n", numberOfDifferentColors);

    for(int i = 0; i < n; ++i)
    {
        printf("Vertex %d: color %d\n", i, colors[i]);
    }

    printf("\n");
}

void graphColoring(graph_t* graph)
{
    if(graph->isDirected)
    {
        printf("Coloring works only for non-directed graphs!\n\n");
        return;
    }

    int* vertexOrderedByDegree = orderVertex(graph);

    int* colors = (int*)calloc(graph->numberOfVertex, sizeof(int));

    int numberOfDifferentColors = welshPowell(graph, vertexOrderedByDegree, colors);

    printColors(colors, numberOfDifferentColors, graph->numberOfVertex);

    free(colors);
    free(vertexOrderedByDegree);
}

void printPath(graph_t* graph, int* predecessors, int startVertex, int endVertex)
{
    int end = endVertex;

    stack_t* stack = stackCreate();

    int cost = 0;

    while (endVertex != -1)
    {
        stackPush(stack, endVertex);

        if(predecessors[endVertex] != -1)
            cost += graph->adjacencyMatrix[predecessors[endVertex]][endVertex];

        endVertex = predecessors[endVertex];
    }

    if(cost == 0)
    {
        printf("There is no circuit from %d to %d!\n\n", startVertex, end);
    }
    else
    {
        printf("From %d to %d: ", startVertex, end);
    }
    

    while(!stackIsEmpty(stack))
    {
        int currentVertex = stackPop(stack);

        if(cost != 0) printf("%d ", currentVertex);
    }

    if(cost != 0) printf("(cost = %d)\n\n", cost);

    stackDestroy(&stack);
}

int _printMST(graph_t* graph, int* parents, int node, int depth)
{
    for (int i = 0; i < depth; ++i) printf("  ");

    if (depth > 0) printf("| ");

    printf("Vertex %d\n", node);

    int actualCost = 0;
    for (int i = 0; i < graph->numberOfVertex; ++i)
    {
        if (parents[i] == node)
        {
            actualCost += graph->adjacencyMatrix[node][i] + _printMST(graph, parents, i, depth + 1);
        }
    }

    return actualCost;
}

int printMST(graph_t* graph, int* parents)
{
    int root = -1;

    printf("Tree:\n");

    for (int i = 0; i < graph->numberOfVertex; ++i)
    {
        if (parents[i] == -1)
        {
            root = i;
            break;
        }
    }

    if (root != -1)
    {
        return _printMST(graph, parents, root, 0);
    }

    return 0;
}

void primAlgorithm(graph_t* graph)
{
    int* parents = createPredecessors(graph->numberOfVertex);

    heap_t* priorityQueue = heapCreate(graph->numberOfVertex, 0, TRUE);

    while(!heapIsEmpty(priorityQueue))
    {
        int currentVertex = heapPop(priorityQueue);
        heapMin(priorityQueue, 0);

        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatrix[currentVertex][i] != 0)
            {
                if(isInHeap(priorityQueue, i))
                {
                    int heapPosition = heapFind(priorityQueue, i);

                    if(priorityQueue->queue[heapPosition] > graph->adjacencyMatrix[currentVertex][i])
                    {
                        priorityQueue->queue[heapPosition] = graph->adjacencyMatrix[currentVertex][i];

                        parents[i] = currentVertex;

                        heapMin(priorityQueue, 0);
                    }
                }
            }
        }
        
    }

    int totalCost = printMST(graph, parents);
    printf("\nTotal Cost: %d\n\n", totalCost);

    heapDelete(&priorityQueue);
    free(parents);
}

BOOL relax(heap_t* heap, int d, int v, int weight, BOOL find)
{
    int index = v;

    if(find)
    {
        index = heapFind(heap, v);
    }

    if(d == __INT_MAX__) return FALSE;

    if(heap->queue[index] > d + weight)
    {
        heap->queue[index] = d + weight;

        return TRUE;
    }

    return FALSE;
}

void printAllPaths(graph_t* graph, int* predecessors, int startVertex)
{
    printf("********** Paths from %d **********\n\n", startVertex);

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        if(i != startVertex) printPath(graph, predecessors, startVertex, i);
    }  

    printf("\n");
}

void djikistraAlgorithm(graph_t* graph, int startVertex)
{
    if(vertexIsInvalid(startVertex, graph->numberOfVertex))
    {
        printf("Insert a valid start vertex!\n\n");
        
        return;
    }

    printf("Graph has only positive weights! Running Djikstra' Algorithm!\n\n");

    heap_t* priorityQueue = heapCreate(graph->numberOfVertex, startVertex, TRUE);

    int* predecessors = createPredecessors(graph->numberOfVertex);

    while(!heapIsEmpty(priorityQueue))
    {
        int d = priorityQueue->queue[0];

        int currentVertex = heapPop(priorityQueue);

        for(int i = 0; i < graph->numberOfVertex; ++i)
        {
            if(graph->adjacencyMatrix[currentVertex][i] != 0 && isInHeap(priorityQueue, i))
            {
                if(relax(priorityQueue, d, i, graph->adjacencyMatrix[currentVertex][i], TRUE))
                {
                    predecessors[i] = currentVertex;
                }
            }
        }

        heapMin(priorityQueue, 0);
    }   

    printAllPaths(graph, predecessors, startVertex);

    heapDelete(&priorityQueue);

    free(predecessors);
}

BOOL graphHasNegativeCycle(graph_t* graph, heap_t* vectors)
{
    for(int u = 0; u < graph->numberOfVertex; ++u)
    {
        for(int v = 0; v < graph->numberOfVertex; ++v)
        {
            if(graph->adjacencyMatrix[u][v] != 0)
            {
                if(relax(vectors, vectors->queue[u], v, graph->adjacencyMatrix[u][v], FALSE)) return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL bellmanFordAlgorithm(graph_t* graph, int startVertex, BOOL print)
{
    if(vertexIsInvalid(startVertex, graph->numberOfVertex))
    {
        printf("Insert a valid start vertex!\n\n");

        return TRUE;
    }

    printf("Graph has at least one negative weight! Running Bellman-Ford' Algorithm!\n\n");

    heap_t* vectors = heapCreate(graph->numberOfVertex, startVertex, FALSE);

    int* predecessors = createPredecessors(graph->numberOfVertex);

    for(int i = 0; i < graph->numberOfVertex - 1; ++i)
    {
        for(int u = 0; u < graph->numberOfVertex; ++u)
        {
            for(int v = 0; v < graph->numberOfVertex; ++v)
            {
                if(graph->adjacencyMatrix[u][v] != 0)
                {
                    if(relax(vectors, vectors->queue[u], v, graph->adjacencyMatrix[u][v], FALSE))
                    {
                        predecessors[v] = u;
                    }
                }
            }
        }
    }

    if(graphHasNegativeCycle(graph, vectors))
    {
        printf("Finding a shortest path is not possible, graph has a negative cycle!\n\n");

        heapDelete(&vectors);

        free(predecessors);

        return TRUE;
    }

    if(print)
    {
        printAllPaths(graph, predecessors, startVertex);
    }
    
    heapDelete(&vectors);

    free(predecessors);

    return FALSE;
}

void floydWarshallAlgorithm(graph_t* graph)
{
    int** floydAdjMatrix = createFloydAdjMatrix(graph->adjacencyMatrix, graph->numberOfVertex);
    int** floydPredMatrix = createFloydPredecessorsMatrix(graph->adjacencyMatrix, graph->numberOfVertex);

    for(int k = 0; k < graph->numberOfVertex; ++k)
    {
        for(int u = 0; u < graph->numberOfVertex; ++u)
        {
            for(int v = 0; v < graph->numberOfVertex; ++v)
            {
                if(floydAdjMatrix[u][k] == __INT_MAX__ || floydAdjMatrix[k][v] == __INT_MAX__) continue;

                if(floydAdjMatrix[u][v] > floydAdjMatrix[u][k] + floydAdjMatrix[k][v])
                {
                    floydAdjMatrix[u][v] = floydAdjMatrix[u][k] + floydAdjMatrix[k][v];
                    floydPredMatrix[u][v] = floydPredMatrix[k][v];
                }
            }
        }
    }

    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        printAllPaths(graph, floydPredMatrix[i], i);
    }

    matrixDelete(&floydAdjMatrix, graph->numberOfVertex);

    matrixDelete(&floydPredMatrix, graph->numberOfVertex);

    return;
}

BOOL graphHasNegativeWeight(graph_t* graph)
{
    for(int i = 0; i < graph->numberOfVertex; ++i)
    {
        for(int j = 0; j < graph->numberOfVertex; ++j)
        {
            if(graph->adjacencyMatrix[i][j] < 0) return TRUE;
        }
    }

    return FALSE;
}

void graphDelete(graph_t** graph)
{
    if(graph == NULL || *graph == NULL) return;

    matrixDelete(&((*graph)->adjacencyMatrix), (*graph)->numberOfVertex);

    free(*graph);

    *graph = NULL;
}