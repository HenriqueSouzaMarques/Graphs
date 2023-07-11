#ifndef GRAPH_H
#define GRAPH_H

#define BOOL char
#define TRUE 1
#define FALSE 0

#include "../Includes/queue.h"
#include "../Includes/stack.h"
#include "../Includes/heap.h"

typedef struct graph graph_t;

/* Graph manipulation functions */
graph_t* graphCreate(int numberOfVertex, BOOL isDirected);
void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight);
void graphRemoveEdge(graph_t* graph, int vertexA, int vertexB);
void graphDelete(graph_t** graph);

/* Graph traversing algorithm's */
int graphBFS(graph_t* graph, BOOL print);
queue_t* graphDFS(graph_t* graph, BOOL print, BOOL topologicalOrdering);

/* Eulerian Cycles in graphs */
BOOL graphNotEulerian(graph_t* graph);
void graphEulerianCircuit(graph_t* graph, int startVertex);

/* Graph coloring (Welsh Powell Algorithm)*/
void graphColoring(graph_t* graph);

/* Strongly Connected Components (SCC) in graphs */
int tarjanAlgorithm(graph_t* graph);

/* Minimum Spanning Tree (MST) */
void primAlgorithm(graph_t* graph);

/* Shortest paths algorithms */
void djikistraAlgorithm(graph_t* graph, int startVertex);
BOOL bellmanFordAlgorithm(graph_t* graph, int startVertex, BOOL print);
void floydWarshallAlgorithm(graph_t* graph);

/* Control functions */
BOOL getIsDirected(graph_t* graph);
BOOL graphHasNegativeWeight(graph_t* graph);


#endif // GRAPH_H