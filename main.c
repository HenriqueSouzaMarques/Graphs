#include <stdio.h>
#include <stdlib.h>

#include "Includes/user.h"

void printMenu()
{
    printf("   *** Options ***   \n");
    printf("1. Create Graph \n");
    printf("2. Add Edge \n");
    printf("3. Delete Edge \n");
    printf("4. BFS Search \n");
    printf("5. DFS Search \n");
    printf("0. Exit Program \n\n\n");

    printf("Choose one of the options above: ");
}


int main()
{
    int option;
    BOOL isDirected;

    graph_t* graph = NULL;

    do
    {
        printMenu();
        scanf("%d", &option);
        printf("\n");

        switch (option)
        {
            case 1:
                graph = userCreateGraph(&isDirected);
                break;
            
            case 2:
                userGraphAddEdge(graph, isDirected);
                break;

            case 3:
                userGraphRemoveEdge(graph, isDirected);
                break;

            case 4:
                userGraphBFS(graph, isDirected);
                break;

            case 5:
                userGraphDFS(graph, isDirected);
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