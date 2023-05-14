#ifndef USER_H
#define USER_H

#include "graph.h"

graph_t* userCreateGraph();

void userGraphAddEdge(graph_t* graph);

void userGraphRemoveEdge(graph_t* graph);

void userGraphBFS(graph_t* graph);

void userGraphDFS(graph_t* graph);

void userGraphFindEulerianCycle(graph_t* graph);

void userExitProgram(graph_t** graph);


#endif // USER_H