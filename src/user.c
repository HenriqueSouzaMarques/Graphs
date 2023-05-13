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

graph_t* userCreateGraph(BOOL* isDirected)
{   
    int numberOfVertex;

    printf("Put the number of vertex of your graph: ");
    scanf("%d", &numberOfVertex);
    printf("\n");

    char directed;
    printf("Is you graph directed? (Y/N): ");
    scanf(" %c", &directed);

    *isDirected = (directed == 'Y') ? TRUE : FALSE;

    printf("\n");
    clear();

    return graphCreate(numberOfVertex);
}

void userGraphAddEdge(graph_t* graph, BOOL isDirected)
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

    graphAddEdge(graph, vertexA, vertexB, weight, isDirected);

    clear();
}

void userGraphRemoveEdge(graph_t* graph, BOOL isDirected)
{
    int vertexA, vertexB;

    printf("Type the vertex A: ");
    scanf("%d", &vertexA);
    printf("\n");

    printf("Type the vertex B: ");
    scanf("%d", &vertexB);
    printf("\n");  

    graphRemoveEdge(graph, vertexA, vertexB, isDirected);  

    clear();
}

void userGraphBFS(graph_t* graph, BOOL isConected)
{
    int numberOfConnectedComponents = graphBFS(graph);

    printf("There are %d connected(s) component(s) in this graph!\n", numberOfConnectedComponents);        

    clear();
}

void userGraphDFS(graph_t* graph, BOOL isConected)
{
    int numberOfConnectedComponents = graphDFS(graph);

    printf("There are %d connected(s) component(s) in this graph!\n", numberOfConnectedComponents);

    clear();
}

void userExitProgram(graph_t** graph)
{
    graphDelete(graph);

    printf("Thanks for using the program!\n\n\n");
}