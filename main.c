#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main()
{
    node_t * list_one;

    create_empty_list(&list_one);

    push(&list_one,5);

    for(int i = 0; i < 5; i++)
    {
        push(&list_one,i*i);
    }

    print_nodes(list_one);
    printf("\nitem count of list_one: %i\n\n",get_count(list_one));


    clear_nodes(list_one);
    return 0;
}

