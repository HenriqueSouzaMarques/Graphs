#include <stdio.h>
#include <stdlib.h>

#include "../Includes/user.h"

void clear()
{
    scanf("%*c");

    printf("Press any key to continue: ");
    scanf("%*c");

    system("clear");
}

graph_t* userCreateGraph()
{   
    int numberOfVertex;

    printf("Put the number of vertex of your graph: ");
    scanf("%d", &numberOfVertex);
    printf("\n");

    BOOL isDirected;
    printf("Is you graph directed? (Y/N): ");
    scanf(" %c", &isDirected);

    isDirected = (isDirected == 'Y') ? TRUE : FALSE;

    printf("\n");
    clear();

    return graphCreate(numberOfVertex, isDirected);
}

void userGraphAddEdge(graph_t* graph)
{
    int vertexA, vertexB, weight;

    printf("Type the vertex A (vertex starts with 0): ");
    scanf("%d", &vertexA);
    printf("\n");

    printf("Type the vertex B (vertex start with 0): ");
    scanf("%d", &vertexB);
    printf("\n");

    printf("Type the weight of the edge (must be a positive integer): ");
    scanf("%d", &weight);
    printf("\n");

    graphAddEdge(graph, vertexA, vertexB, weight);

    clear();
}

void userGraphRemoveEdge(graph_t* graph)
{
    int vertexA, vertexB;

    printf("Type the vertex A: ");
    scanf("%d", &vertexA);
    printf("\n");

    printf("Type the vertex B: ");
    scanf("%d", &vertexB);
    printf("\n");  

    graphRemoveEdge(graph, vertexA, vertexB);  

    clear();
}

void userGraphBFS(graph_t* graph)
{
    int numberOfConnectedComponents = graphBFS(graph, TRUE);

    printf("There are %d connected(s) component(s) in this graph!\n", numberOfConnectedComponents);        

    clear();
}

void userGraphDFS(graph_t* graph)
{
    int numberOfConnectedComponents = graphDFS(graph, TRUE);

    printf("There are %d connected(s) component(s) in this graph!\n", numberOfConnectedComponents);

    clear();
}

void userGraphFindEulerianCycle(graph_t* graph)
{
    if(getIsDirected(graph) || graphNotEulerian(graph))
    {
        printf("Your graph is not eulerian!\n");

        return;
    }

    int startVertex;

    printf("Insert the starting vertex: ");

    scanf("%d", &startVertex);

    graphEulerianCircuit(graph, startVertex);

    clear();
}

void userGraphColouring(graph_t* graph)
{
    graphColouring(graph);
    
    clear();
}

void userExitProgram(graph_t** graph)
{
    graphDelete(graph);

    printf("Thanks for using the program!\n\n\n");
}