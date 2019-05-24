//
// Created by Jesse Smith on 2019-05-16.
//

#ifndef LINKEDLIST_LINKED_LIST_H
#define LINKEDLIST_LINKED_LIST_H

typedef union {
   float number;
   char string[20];
} Data;

typedef struct Node Node;

struct Node {
    Data data;
    Node *next;
};

typedef struct {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

int initialize_linked_list(LinkedList *list);

int size(LinkedList *list);

void insert(LinkedList *list, Data d);

void insertFirst(LinkedList *list, Data d);

Data* get(LinkedList *list, int index);

Data* pop(LinkedList *list, int index);

#endif //LINKEDLIST_LINKED_LIST_H
