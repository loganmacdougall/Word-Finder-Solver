#ifndef __HEADER_LINKED_LIST
#define __HEADER_LINKED_LIST

#include <stdlib.h>
#include <string.h>

typedef struct _LinkedListNode {
  void *data;
  struct _LinkedListNode *next;
} LinkedListNode;

typedef struct _LinkedList {
  LinkedListNode *head, *tail;
  int length;
  int element_size;
} LinkedList;

LinkedList *linkedlist_init(int element_size);
int linkedlist_length(LinkedList *list);
void linkedlist_push_front(LinkedList *list, void *data);
void linkedlist_push_back(LinkedList *list, void *data);
void *linkedlist_pop_front(LinkedList *list);
void linkedlist_destroy(LinkedList *list);

void _linkedlist_put_first_element(LinkedList *list, void *data);
LinkedListNode *_linkedlist_init_node(void *data, int size);
void _linkedlist_destroy_node(LinkedListNode *node);

#endif
