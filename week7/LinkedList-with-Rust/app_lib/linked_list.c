//
// Created by Jesse Smith on 2019-05-16.
//

#include <stdlib.h>

#include "linked_list.h"

#include "../linkedlist-ffi/src/rust_linked_list.h"

int initialize_linked_list(struct LinkedList *list)
{
    list->size = 0;
    list->head = list->tail = NULL;
    return 0;
}

//extern int size(struct LinkedList *list);

//int size(LinkedList *list)
//{
//    return list->size;
//}

void insert(struct LinkedList *list, struct Data d)
{
    struct Node *n = (struct Node*) malloc (sizeof(struct Node));
    n->next = NULL;
    n->data = d;

    if (list->size == 0) {
        list->head = n;
        list->tail = list->head;
    } else {
        list->tail->next = n;
        list->tail = n;
    }

    list->size += 1;
}

void insertFirst(struct LinkedList *list, struct Data d)
{
    struct Node *n = (struct Node*) malloc (sizeof(struct Node));
    n->next = NULL;
    n->data = d;

    if (list->size == 0) {
        list->head = n;
        list->tail = list->head;
    } else {
        n->next = list->head;
        list->head = n;
    }

    list->size++;
}

struct Data* get(struct LinkedList *list, int index)
{
    if (index >= list->size || index < 0) {
        return NULL;
    }

    struct Node *curr = list->head;
    for (; index > 0; index--) {
        curr = curr->next;
    }

    return &(curr->data);
}

struct Data* pop(struct LinkedList *list, int index)
{
    if (index >= list->size || index < 0) {
        return NULL;
    }

    struct Node *curr;
    struct Data *result;

    if (list->size == 1) { //popping only thing
        curr = list->head;
        result = &(curr->data);
        list->head = list->tail = NULL;
    }

    else if (index == 0) { //popping first
        result = &(list->head->data);
        curr = list->head;
        list->head = curr->next;
    }

    else {
        curr = list->head;
        struct Node *prev = curr;
        for (; index > 0; index--) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        if (index == list->size-1)
            list->tail = prev;

        result = &(curr->data);
    }

    free(curr);
    list->size--;
    return result;
}