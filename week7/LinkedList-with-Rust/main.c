#include <stdio.h>
#include <stdlib.h>
#include "app_lib/linked_list.h"

int main() {
    struct LinkedList *list = (struct LinkedList*) malloc(sizeof (struct LinkedList));
    initialize_linked_list(list);

    struct Data data1 = { .number = 1 };
    struct Data data2 = { .number = 3 };
    struct Data data3 = { .string = "Hello" };
    struct Data data4 = { .string = "World" };

    insert(list, data1);
    insert(list, data2);
    insertFirst(list, data4);
    insertFirst(list, data3);

    //prints: Hello World 1.00 3.00
    for (int i = 0; i < size(list); i++) {
        struct Data *d = get(list, i);
        if (i < 2)
            printf("%s ", d->string);
        else
            printf("%0.2f ", d->number);
    }

    return 0;
}