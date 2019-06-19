
#define TRUE 1
#define FALSE 0

typedef union {
    int initialData;
}node_data;

typedef struct node{
    int val;
    struct node  * next;
    node_data headData;
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

/** Creates a linked list with the initial to be null **/
int create_empty_list(node_t ** head)
{
    node_t * head_node = create_node(-1);
    head_node->headData.initialData = FALSE;

    if(head_node == NULL)
    {
        printf("Failed to create new list, malloc failed\n");
        return FALSE;
    }

    head_node->headData.initialData = FALSE;
    *head = head_node;
    printf("Created linked list\n");
    return TRUE;
}

/** Creates a new linked list **/
int create_list(node_t ** head,int initial_value)
{
    node_t * head_node = create_node(initial_value);
    head_node->headData.initialData  = TRUE;

    if(head_node == NULL)
    {
        printf("Failed to create new list, malloc failed\n");
        return FALSE;
    }

    head_node->headData.initialData = TRUE;
    *head = head_node;
    printf("Created linked list\n");
    return TRUE;
}

/** Deletes a node **/
int delete_node(node_t * node)
{
    int node_val = node->val;
    free(node);
    node = NULL;
    printf("Node removed: val->%d\n",node_val);
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

/** Removes a node at the given index **/
int pop_at_index(node_t ** head_node,int index)
{
    if(index == 0)
    {
        return pop(head_node);
    }

    printf("\nGoing to remove node at index: %d\n",index);

    node_t * current = *head_node;
    node_t * prev_node;
    int counter = 0;

    while(current != NULL)
    {
        // index reached
        if(counter == index)
        {
            if(current->next == NULL)
            {
                prev_node->next = NULL;
            }
            else
            {
                prev_node->next = current->next;
            }
            return delete_node(current);
        }

        // end of the list
        if(current->next == NULL)
        {
            printf("Node at index: %d not found\n",index);
            return FALSE;
        }

        prev_node = current;
        current = current->next;
        counter++;
    }

    printf("Failed to remove node at index: %d\n",index);
    return FALSE;
}

/** Removes the last node **/
int pop_end(node_t * head_node)
{
    node_t * current = head_node;
    node_t * prev_node;

    printf("\nRemoving last node\n");

    while(current != NULL)
    {
        // Found last node
        if(current->next == NULL)
        {
            prev_node->next = NULL;
            return delete_node(current);;
        }

        prev_node = current;
        current = current->next;
    }
    printf("Failed to remove last node\n");
    return FALSE;
}

/** Remove a node when the value equals x **/
int pop_at_value(node_t * head_node, int value)
{
    node_t * current = head_node;
    node_t * prev_node;

    printf("\nGoing to remove node if value equals %d\n",value);

    while(current != NULL)
    {
        if(current->val == value)
        {
            if(current->next != NULL)
            {
                prev_node->next = current->next;
            }
            else
            {
                prev_node->next = NULL;
            }
            return delete_node(current);
        }

        if(current->next == NULL)
        {
            printf("Failed to find node with value: %d\n",value);
            return FALSE;
        }

        prev_node = current;
        current = current->next;
    }

    printf("Failed to remove node\n");
    return FALSE;
}

/** Add a node at the start of the node **/
int push(node_t ** head_node, int val)
{
    printf("Going to add node at the begin\n");
    node_t * head = *head_node;

    if(head->headData.initialData == FALSE)
    {
        head->val = val;
        head->headData.initialData = TRUE;
        printf("List was created with no initial value, %d has been placed at the head\n",val);
        return TRUE;
    }

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

/** Add a node at a given index **/
int push_at_index(node_t ** head_node, int index, int val)
{
    if(index == 0)
    {
        return push(head_node,val);
    }

    printf("Going to insert node at index: %d\n", index);

    node_t * current = *head_node;
    node_t * prev_node;
    int counter = 0;

    while(current != NULL)
    {
        // reached insert point
        if(counter == index)
        {
            node_t * new_node = create_node(val);
            prev_node->next = new_node;
            new_node->next = current;
            printf("Inserted node at index: %d\n",index);
            return TRUE;
        }

        // reached end of the list
        if(current->next == NULL)
        {
            node_t * new_node = create_node(val);
            current->next = new_node;
            printf("%d is bigger than list size, node added at the end\n",index);
            return TRUE;
        }

        counter++;
        prev_node = current;
        current = current->next;
    }

    printf("Failed to insert node t index: %d\n", index);
    return FALSE;
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
