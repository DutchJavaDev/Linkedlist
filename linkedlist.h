#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NODE_nodeSignature 110

#define ERROR_MALLOC_FAILED 2
#define ERROR_NODE_NULL 3

typedef struct
{
    void* nodeData;
    struct NODE* nextNode;
    char nodeSignature;
} NODE;

/// Debug purpose
void print_nodes_int(NODE* head)
{
    NODE* current = head;

    while(current != NULL)
    {
        printf("node value: %d\n",(int)current->nodeData);

        current = current->nextNode;
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
        current = current->nextNode;
        delete_node(temp);
    }
}

/// Creates a new node with a given value
int create_node(void* node_nodeData, NODE** _node)
{
    NODE* node = (NODE*) malloc(sizeof(NODE));

    if(node == NULL)
    {
        return ERROR_MALLOC_FAILED;
    }

    node->nodeData = node_nodeData;
    node->nodeSignature = NODE_nodeSignature;
    node->nextNode = NULL;

    *_node = node;
    return TRUE;
}

/// Creates a node with nodeData set to NULL
int create_node_empty(NODE** node)
{
    return create_node(NULL,node);
}

/// Frees the memory the node has being using, sets the value to NULL
int delete_node(NODE* node)
{
    if(node == NULL || node->nodeSignature != NODE_nodeSignature)
        return ERROR_NODE_NULL;

    node->nodeData = NULL;
    node->nextNode = NULL;
    node->nodeSignature = NULL;
    free(node);
    return TRUE;
}

/// Adds a node to the begin of the list, makes the added node the new head
int push(NODE** head, void* nodeData)
{
    if((*head)->nodeData == NULL)
    {
        /// No need to create a new node since the head has no data
        (*head)->nodeData = nodeData;
        return TRUE;
    }

    NODE* new_head;
    int result = nodeData == NULL ? create_node_empty(&new_head) : create_node(nodeData,&new_head);

    /// Something bad :(
    if(result > 1)
        return result;

    new_head->nextNode  = *head;

    *head = new_head;
    return TRUE;
}

/// Removes the first item in the list, update the head node
int pop(NODE** head)
{
    NODE* current = *head;
    NODE* new_head = current->nextNode;

    (*head) = new_head;
    delete_node(current);

    return TRUE;
}
