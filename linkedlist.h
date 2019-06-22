#define TRUE 1
#define FALSE 0
#define NODE_SIGNATURE 110

typedef union {
    int initialData;
}node_data;

typedef struct node{
    int val;
    char base;
    struct node  * next;
    node_data headData;
} node_t;

/** Get the amount of items in the list **/
int get_count(node_t * head_node)
{
    node_t * current = head_node;

    int list_size = 0;

    while(current != NULL)
    {
        if(current->next == NULL)
        {
            list_size++;
            break;
        }

        current = current->next;
        list_size++;
    }

    return list_size;
}

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
node_t * create_empty_list()
{
    node_t * head_node = create_node(-1);

    if(head_node == NULL)
    {
        printf("Failed to create new list, malloc failed\n");
        exit(EXIT_FAILURE);
    }

    head_node->base = NODE_SIGNATURE;
    head_node->headData.initialData = FALSE;
    return head_node;
}

/** Creates a new linked list **/
node_t * create_list(int initial_value)
{
    node_t * head_node = create_node(initial_value);

    if(head_node == NULL)
    {
        printf("Failed to create new list, malloc failed\n");
        exit(EXIT_FAILURE);
    }

    head_node->base = NODE_SIGNATURE;
    head_node->headData.initialData = TRUE;
    return head_node;
}

/** Deletes a node **/
void delete_node(node_t * node)
{
    int node_val = node->val;
    free(node);
    node = NULL;
    printf("Node removed: val->%d\n",node_val);
}

/** Prints out all the elements of the linked list **/
void print_nodes(node_t * head)
{
    /** empty node **/
    if(head->base != NODE_SIGNATURE)
    {
        printf("Head is null\n");
        exit(EXIT_FAILURE);
    }

    node_t * current = head;
    printf("\nNode values\n");

    while(current != NULL)
    {
        printf("%d\n",current->val);
        current = current->next;
    }
    printf("\n");
}

/** Free up all the memory allocated by the nodes**/
void clear_nodes(node_t * head_node)
{

    if(head_node->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

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
}

/** Removes the node item of the list **/
void pop(node_t ** head_node)
{
    if((*head_node)->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    printf("Going to remove first node\n");

    node_t * head = *head_node;
    node_t * new_head = head->next;
    new_head->base = NODE_SIGNATURE;

    *head_node = new_head;

    delete_node(head);
}

/** Removes a node at the given index **/
void pop_at_index(node_t ** head_node,int index)
{
    if((*head_node)->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    if(index == 0)
    {
        pop(head_node);
        return;
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
            delete_node(current);
            return;
        }

        // end of the list
        if(current->next == NULL)
        {
            printf("Node at index: %d not found\n",index);
            exit(EXIT_FAILURE);
        }

        prev_node = current;
        current = current->next;
        counter++;
    }

    printf("Failed to remove node at index: %d\n",index);
    exit(EXIT_FAILURE);
}

/** Removes the last node **/
void pop_end(node_t * head_node)
{
    if(head_node->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    node_t * current = head_node;
    node_t * prev_node;

    printf("\nRemoving last node\n");

    while(current != NULL)
    {
        // Found last node
        if(current->next == NULL)
        {
            prev_node->next = NULL;
            delete_node(current);
            return;
        }

        prev_node = current;
        current = current->next;
    }
    printf("Failed to remove last node\n");
    exit(EXIT_FAILURE);
}

/** Remove a node when the value equals x **/
void pop_at_value(node_t * head_node, int value)
{
    if(head_node->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

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
            delete_node(current);
            return;
        }

        if(current->next == NULL)
        {
            printf("Failed to find node with value: %d\n",value);
            exit(EXIT_FAILURE);
        }

        prev_node = current;
        current = current->next;
    }

    printf("Failed to remove node\n");
    exit(EXIT_FAILURE);
}

/** Add a node at the start of the node **/
void push(node_t ** head_node, int val)
{
    if((*head_node)->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    printf("Going to add node at the begin\n");
    node_t * head = *head_node;

    if(head->headData.initialData == FALSE)
    {
        head->val = val;
        head->headData.initialData = TRUE;
        printf("List was created with no initial value, %d has been placed at the head\n",val);
        return;
    }

    node_t * new_node = create_node(val);

    if(new_node == NULL)
    {
        printf("Failed to add node at begin\n");
        exit(EXIT_FAILURE);
    }

    new_node->next = head;
    new_node->base = NODE_SIGNATURE;
    *head_node = new_node;
    printf("Node added at the begin\n");
}

/** Add a node at a given index **/
void push_at_index(node_t ** head_node, int index, int val)
{
    if((*head_node)->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    if(index == 0)
    {
        push(head_node,val);
        return;
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
            return;
        }

        // reached end of the list
        if(current->next == NULL)
        {
            node_t * new_node = create_node(val);
            current->next = new_node;
            printf("%d is bigger than list size, node added at the end\n",index);
            return;
        }

        counter++;
        prev_node = current;
        current = current->next;
    }

    printf("Failed to insert node t index: %d\n", index);
    exit(EXIT_FAILURE);
}

/** Adds a node at the end **/
void push_end(node_t * head_node, int val)
{
    if(head_node->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

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
                exit(EXIT_FAILURE);
            }

            current->next = new_node;
            printf("Node added at the end\n");
            return;
        }
        else
        {
            current = current->next;
        }
    }
    printf("Failed to add node at the end\n");
    exit(EXIT_FAILURE);
}

/** Reverses the linked list **/
void reverse_list(node_t ** head)
{
    if((*head)->base != NODE_SIGNATURE)
    {
        printf("Head is null");
        exit(EXIT_FAILURE);
    }

    node_t * next_node = (*head)->next;
    node_t * prev_node = *head;
    node_t * temp_node;

    (*head)->next = NULL;
    node_data * head_data = &(*head)->headData;

    printf("Going to reverse list\n");

    while(next_node != NULL)
    {
        temp_node = next_node->next;

        if(temp_node == NULL)
        {
            /** Reached end node **/
            next_node->next = prev_node;
            next_node->headData = *head_data;
            next_node->base = NODE_SIGNATURE;

            (*head)->base = 0;
            *head = next_node;
            printf("List reversed\n");
            return;
        }

        /** Reversing the the connections **/
        next_node->next = prev_node;

        prev_node = next_node;

        next_node = temp_node;
    }

    printf("Failed to reverse list\n");
    exit(EXIT_FAILURE);
}
