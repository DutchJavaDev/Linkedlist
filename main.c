#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listmanager.h"



int main()
{
    NODE* intList;
    int intListIndex;

    NODE* stringList;
    int stringListIndex;

    intListIndex = create_list(&intList);
    push(&intList,465);

    stringListIndex = create_list(&stringList);
    push(&stringList, "Hello LinkedList");
    push(&stringList, "Hello World");

    print_nodes_int(&intList);

    printf("\n");

    print_nodes_string(&stringList);

    dispose();


    /*int lenght = 3;
    NODE** array;

    /// Allocate memory for n amount of NODES
    /// Is array, access by []
    array = malloc(sizeof(NODE*) * lenght);

    for(int i = 0; i < lenght; i++)
    {
        NODE* current = &array[i];

        printf("Data of node: %i\n", i);
        if(current->nodeSignature == NODE_nodeSignature)
        {
            printf("same\n");
        }
        else
        {
            printf("not same\n");
        }
        printf("\n");
    }

    printf("\n");

    /// Create NODES
    NODE* intList;
    create_list(&intList);

    NODE* stringList;
    create_node("Programming is epic", &stringList);

    NODE* charList;
    create_node_empty(&charList);

    /// Fill the NODE pointer array with the addresses of the created lists
    array[0] = &intList;
    array[1] = &stringList;
    array[2] = &charList;

    /// Test by pushing data in to them
    push(array[0], 15);
    push(array[0],1337);

    push(array[1], "C pointer array is hard");
    push(array[1], "C pointers are a mess for me :/");

    push(array[2], 'S');
    push(array[2], 'I');
    push(array[2], 'R');
    push(array[2], 'O');
    push(array[2], 'B');

    /// Print data out using the pointer in the pointer array
    print_nodes_int(array[0]);
    print_nodes_string(array[1]);
    print_nodes_char(array[2]);

    /// Clear data out
    for(int i = 0; i < lenght; i++)
    {
        delete_all_nodes(array[i]);
    }
    //delete_all_nodes(array[0]);
    //delete_all_nodes(array[1]);
    //delete_all_nodes(array[2]);

    /// Clear pointer NODE array
    free(array);*/
    return 0;
}

