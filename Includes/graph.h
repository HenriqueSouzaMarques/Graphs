#ifndef GRAPH_H
#define GRAPH_H

#define BOOL char
#define TRUE 1
#define FALSE 0

typedef struct graph graph_t;

graph_t* graphCreate(int numberOfVertex);

void graphAddEdge(graph_t* graph, int vertexA, int vertexB, int weight, BOOL isDirected);

void graphRemoveEdge(graph_t* graph, int vertexA, int vertexB, BOOL isDirected);

int graphBFS(graph_t* graph);

int graphDFS(graph_t* graph);

void graphDelete(graph_t** graph);

#endif // GRAPH_H