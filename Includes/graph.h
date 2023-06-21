#ifndef GRAPH_H
#define GRAPH_H

#define BOOL char
#define TRUE 1
#define FALSE 0

#include "../Includes/queue.h"
#include "../Includes/stack.h"
#include "../Includes/heap.h"

typedef struct graph graph_t;

graph_t* graphCreate(int numberOfVertex, BOOL isDirected);

void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight);
void graphRemoveEdge(graph_t* graph, int vertexA, int vertexB);

int graphBFS(graph_t* graph, BOOL print);
int graphDFS(graph_t* graph, BOOL print);

BOOL graphNotEulerian(graph_t* graph);
void graphEulerianCircuit(graph_t* graph, int startVertex);

void graphColoring(graph_t* graph);

int tarjanAlgorithm(graph_t* graph);

void djikistraAlgorithm(graph_t* graph, int startVertex);
void bellmanFordAlgorithm(graph_t* graph, int startVertex);

BOOL getIsDirected(graph_t* graph);

BOOL graphHasNegativeWeight(graph_t* graph);

void graphDelete(graph_t** graph);

#endif // GRAPH_H