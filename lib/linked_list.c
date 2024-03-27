#include "linked_list.h"

LinkedList *linkedlist_init(int element_size) {
  LinkedList *list = malloc(sizeof(*list));

  list->length = 0;
  list->element_size = element_size;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

int linkedlist_length(LinkedList *list) { return list->length; }

void linkedlist_push_front(LinkedList *list, void *data) {
  if (list->length == 0)
    return _linkedlist_put_first_element(list, data);

  LinkedListNode *node = _linkedlist_init_node(data, list->element_size);
  node->next = list->head;
  list->head = node;
  list->length++;
}

void linkedlist_push_back(LinkedList *list, void *data) {
  if (list->length == 0)
    return _linkedlist_put_first_element(list, data);

  LinkedListNode *node = _linkedlist_init_node(data, list->element_size);
  list->tail->next = node;
  list->tail = node;
  list->length++;
}

void *linkedlist_pop_front(LinkedList *list) {
  if (list->length == 0)
    return NULL;

  LinkedListNode *node = list->head;
  void *data = node->data;
  list->head = node->next;
  free(node);
  list->length--;

  return data;
}

void linkedlist_destroy(LinkedList *list) {
  LinkedListNode *node = list->head;

  while (node != NULL) {
    LinkedListNode *nextNode = node->next;
    _linkedlist_destroy_node(node);
    node = nextNode;
  }

  free(list);
}

void _linkedlist_put_first_element(LinkedList *list, void *data) {
  if (list->length != 0)
    return;

  list->head = _linkedlist_init_node(data, list->element_size);
  list->tail = list->head;
  list->length = 1;
}

LinkedListNode *_linkedlist_init_node(void *data, int size) {
  LinkedListNode *node = malloc(sizeof(*node));

  node->data = malloc(size);
  memcpy(node->data, data, size);

  node->next = NULL;

  return node;
}

void _linkedlist_destroy_node(LinkedListNode *node) {
  free(node->data);
  free(node);
}
