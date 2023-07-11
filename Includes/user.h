#ifndef USER_H
#define USER_H

#include "graph.h"

graph_t* userCreateGraph();

void userGraphAddEdge(graph_t* graph);

void userGraphRemoveEdge(graph_t* graph);

void userGraphBFS(graph_t* graph);

void userGraphDFS(graph_t* graph);

void userTopologicalSorting(graph_t* graph);

void userGraphFindEulerianCycle(graph_t* graph);

void userGraphColoring(graph_t* graph);

void userFindConnectedComponents(graph_t* graph);

void userMinimumSpanningTree(graph_t* graph);

void userShortestPathSingleSource(graph_t* graph);

void userShortestPathAllSource(graph_t* graph);

void userExitProgram(graph_t** graph);


#endif // USER_H