#ifndef RUST_LINKEDLIST_LINKED_LIST_H
#define RUST_LINKEDLIST_LINKED_LIST_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
//#include <new>

struct Data {
  float number;
  const char *string;
};

struct Node {
  struct Data data;
  struct Node *next;
};

struct LinkedList {
  int32_t size;
  struct Node *head;
  struct Node *tail;
};

//extern "C" {

int32_t size(const struct LinkedList *list);

//} // extern "C"

#endif // RUST_LINKEDLIST_LINKED_LIST_H