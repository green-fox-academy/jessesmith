//
// Created by Jesse Smith on 2019-05-16.
//

#ifndef LINKEDLIST_LINKED_LIST_H
#define LINKEDLIST_LINKED_LIST_H

#include "../linkedlist-ffi/src/rust_linked_list.h"
//
//typedef struct {
//   float number;
//   char string[20];
//} Data;
//
//typedef struct Node Node;
//
//struct Node {
//    Data data;
//    Node *next;
//};
//
//typedef struct {
//    Node *head;
//    Node *tail;
//    int size;
//} LinkedList;

int initialize_linked_list(struct LinkedList *list);

//int size(LinkedList *list);

void insert(struct LinkedList *list, struct Data d);

void insertFirst(struct LinkedList *list, struct Data d);

struct Data* get(struct LinkedList *list, int index);

struct Data* pop(struct LinkedList *list, int index);

#endif //LINKEDLIST_LINKED_LIST_H
