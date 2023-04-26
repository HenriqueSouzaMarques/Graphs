#ifndef USER_H
#define USER_H

#include "graph.h"

graph_t* userCreateGraph(BOOL* isDirected);

void userGraphAddEdge(graph_t* graph, BOOL isDirected);

void userGraphRemoveEdge(graph_t* graph, BOOL isDirected);

void userGraphBFS(graph_t* graph, BOOL isDirected);

void userGraphDFS(graph_t* graph, BOOL isDirected);

void userExitProgram(graph_t** graph);


#endif // USER_H