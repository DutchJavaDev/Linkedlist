#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node{
    int val;
    struct node  * next;
} node_t;

/** Creates a new node **/
node_t * create_node(int val)
{
    node_t * new_node = malloc(sizeof(node_t));

    if(new_node == NULL)
    {
        fprintf(stderr,"malloc failed for a new node");
        return NULL;
    }

    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

/** Deletes a node **/
int delete_node(node_t * node)
{
    free(node);
    node = NULL;
    printf("Node removed\n");
    return (node == NULL);
}

/** Prints out all the elements of the linked list **/
int print_nodes(node_t * head)
{
    if(head == NULL)
    {
        printf("Head is null\n");
        return FALSE;
    }


    node_t * current = head;
    printf("\nNode values\n");

    while(current != NULL)
    {
        printf("%d\n",current->val);
        current = current->next;
    }
    printf("\n");
    return TRUE;
}

/** Free up all the memory allocated by the nodes**/
int clear_nodes(node_t * head_node)
{
    node_t * current = head_node;
    node_t * prev_node;

    printf("Removing all nodes\n");

    while(current != NULL)
    {
        if(current->next != NULL)
        {
            prev_node = current;
            current = current->next;

            delete_node(prev_node);
        }
        else
        {
            delete_node(current);
            break;
        }
    }
    return TRUE;
}

/** Removes the node item of the list **/
int pop(node_t ** head_node)
{
    printf("Going to remove first node\n");
    node_t * head = *head_node;

    node_t * new_head = head->next;

    *head_node = new_head;

    return delete_node(head);
}

/** Removes the last node **/
int pop_end(node_t * head_node)
{
    node_t * current = head_node;
    node_t * prev_node;

    printf("Going to remove node at end\n");

    while(current != NULL)
    {
       if(current->next == NULL)
       {
           prev_node->next = NULL;
           current = NULL;
           return delete_node(current);
       }

       prev_node = current;
       current = current->next;
    }
    fprintf(stderr,"Failed to remove node at end\n");
    return FALSE;
}

/** Add a node at the start of the node **/
int push(node_t ** head_node, int val)
{
    printf("Going to add node at the begin\n");
    node_t * head = *head_node;

    node_t * new_node = create_node(val);

    if(new_node == NULL)
    {
        printf("Failed to add node at begin\n");
        return FALSE;
    }

    new_node->next = head;
    *head_node = new_node;
    printf("Node added at the begin\n");
    return TRUE;
}

/** Adds a node at the end **/
int push_end(node_t * head_node, int val)
{
    node_t * current = head_node;

    printf("Going to add a node at the end\n");

    while(current != NULL)
    {
        if(current->next == NULL)
        {
            node_t * new_node = create_node(val);

            if(new_node == NULL)
            {
                printf("Failed to add node at end\n");
                return FALSE;
            }

            current->next = new_node;
            printf("Node added at the end\n");
            return TRUE;
        }
        else
        {
            current = current->next;
        }
    }
    fprintf(stderr,"Failed to add node at the end\n");
    return FALSE;
}

int main()
{


    return 0;
}

