#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NODE_SIGNATURE 110

#define ERROR_MALLOC_FAILED 2
#define ERROR_NODE_NULL 3

typedef struct
{
    void* Data;
    struct NODE* Next;
    char Signature;
} NODE;
/// Debug purpose
void print_nodes_int(NODE* head)
{
    NODE* current = head;

    while(current != NULL)
    {
        printf("node value: %d\n",(int)current->Data);

        current = current->Next;
    }
    printf("\n\n");
}

/// Clears the nodes from begin to end
void delete_all_nodes(NODE* head)
{
    NODE* current = head;

    while(current != NULL)
    {
        NODE* temp = current;
        current = current->Next;
        delete_node(temp);
    }
}

/// Creates a new node with a given value
int create_node(void* node_data, NODE** _node)
{
    NODE* node = (NODE*) malloc(sizeof(NODE));

    if(node == NULL)
    {
        return ERROR_MALLOC_FAILED;
    }

    node->Data = node_data;
    node->Signature = NODE_SIGNATURE;
    node->Next = NULL;

    *_node = node;
    return TRUE;
}

/// Creates a node with data set to NULL
int create_node_empty(NODE** node)
{
    return create_node(NULL,node);
}

/// Frees the memory the node has being using, sets the value to NULL
int delete_node(NODE* node)
{
    if(node == NULL || node->Signature != NODE_SIGNATURE)
        return ERROR_NODE_NULL;

    node->Data = NULL;
    node->Next = NULL;
    node->Signature = NULL;
    free(node);
    return TRUE;
}

/// Adds a node to the begin of the list, makes the added node the new head
int push(NODE** head, void* data)
{
    NODE* new_head;
    int result = data == NULL ? create_node_empty(&new_head) : create_node(data,&new_head);

    /// Something bad :(
    if(result > 1)
        return result;

    new_head->Next  = *head;

    *head = new_head;
    return TRUE;
}

/// Removes the first item in the list, update the head node
int pop(NODE** head)
{
    NODE* current = *head;
    NODE* new_head = current->Next;

    (*head) = new_head;
    delete_node(current);

    return TRUE;
}
