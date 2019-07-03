#include "linkedlist.h"

#define TRUE 1
#define FALSE 0
#define ARRAY_SIZE 10
#define EMPTY_HEADER_NODE -1

NODE** list_references;

/// Creates a NODE* array to store the heads of the lists
void create_array()
{
    list_references = malloc(ARRAY_SIZE * sizeof(NODE*));

    if(list_references == NULL)
    {
        printf("Failed to allocate memory, exit program\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        NODE* current = &list_references[i];
        current->nextNode = NULL;
        current->nodeData = NULL;
        current->nodeSignature = EMPTY_HEADER_NODE;
    }
}

/// Important!, needs to be called before program ends!!!!
void dispose()
{
    clear_all();
    free(list_references);
}

/// Disposes of all the created lists
void clear_all()
{
                        /// Remember if you create an array of 10 nodes its last index
                        /// is 9 -.- spend hours over this bug
                        /// TODO: found out why this behaves like this
    for(int i = 0; i < ARRAY_SIZE-1; i++)
    {
        delete_all_nodes(&list_references[i]);
    }
}

/// Creates a new linkedlist header
int create_list(NODE** headRef)
{
    if(list_references == NULL)
    {
        create_array();
    }

    if(create_node_empty(headRef) == ERROR_MALLOC_FAILED)
    {
        printf("Failed to allocate memory for list header, exit program");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        NODE* current = &list_references[i];

        if(current->nodeSignature == EMPTY_HEADER_NODE)
        {
            list_references[i] = &headRef;
            return i;
        }
    }

    return -1;
}
