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
    printf("0. Exit Program \n\n\n");


    printf("Choose one of the options above: ");

}


int main()
{
    int option;

    graph_t* graph = NULL;

    do
    {
        printMenu();
        scanf("%d", &option);

        switch (option)
        {
            case 1:
                graph = userCreateGraph();
                break;
            
            case 2:
                userGraphAddEdge(graph);
                break;

            case 3:
                userGraphRemoveEdge(graph);
                break;

            case 4:
                userGraphBFS(graph);
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