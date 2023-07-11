#include <stdio.h>
#include <stdlib.h>

#include "Includes/user.h"

void printMenu()
{
    printf("   *** Options ***   \n");
    printf(" 1. Add Edge \n");
    printf(" 2. Delete Edge \n");
    printf(" 3. BFS Search \n");
    printf(" 4. DFS Search \n");
    printf(" 5. Topological Sorting \n");
    printf(" 6. Eulerian Circuit (Fleury's Algorithm) \n");
    printf(" 7. Graph Coloring (Welsh Powell's Algorithm) \n");
    printf(" 8. Finding Connected Components (Tarjan's Algorithm) \n");
    printf(" 9. Finding Minimum Spanning Tree (MST - Prim's Algorithm) \n");
    printf("10 . Single Source Shortest Paths (Djikistra Algorithm / Bellman-Ford Algorithm)\n");
    printf("11. All Pairs Shortest Paths (Floyd-Warshall Algorithm)\n");
    printf(" 0. Exit Program \n\n\n");

    printf("Choose one of the options above: ");
}


int main()
{
    graph_t* graph = userCreateGraph();

    int option;
    do
    {
        printMenu();
        scanf("%d", &option);
        printf("\n");

        switch (option)
        {            
            case 1:
                userGraphAddEdge(graph);
                break;

            case 2:
                userGraphRemoveEdge(graph);
                break;

            case 3:
                userGraphBFS(graph);
                break;

            case 4:
                userGraphDFS(graph);
                break;

            case 5:
                userTopologicalSorting(graph);
                break;

            case 6:
                userGraphFindEulerianCycle(graph);
                break;

            case 7:
                userGraphColoring(graph);
                break;

            case 8:
                userFindConnectedComponents(graph);
                break;
            
            case 9:
                userMinimumSpanningTree(graph);
                break;

            case 10:
                userShortestPathSingleSource(graph);
                break;

            case 11:
                userShortestPathAllSource(graph);
                break;

            case 0:
                userExitProgram(&graph);
                break;

            default:
                printf("Insert a valid option!\n");
                break;
        }

    } while (option != 0);

    return EXIT_SUCCESS;  
}