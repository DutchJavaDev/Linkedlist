#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main()
{
    node_t * list_one;
    node_t * list_two;

    create_empty_list(&list_one);
    create_list(&list_two,5);

    push(&list_one,5);

    for(int i = 0; i < 5; i++)
    {
        push(&list_one,i*i);
        push(&list_two,i*i*i);
    }

    print_nodes(list_one);
    printf("\n");
    print_nodes(list_two);

    clear_nodes(list_one);
    clear_nodes(list_two);
    return 0;
}

