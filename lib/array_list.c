#include "array_list.h"
#include <stdlib.h>

ArrayList *arraylist_init(int element_size) {
  return arraylist_init_set_capacity(element_size, 10);
}

ArrayList *arraylist_init_set_capacity(int element_size, int capacity) {
  ArrayList *list = malloc(sizeof(*list));

  list->capacity = capacity;
  list->size = element_size;
  list->length = 0;

  list->data = calloc(capacity, element_size);

  return list;
}

int arraylist_length(ArrayList *list) { return list->length; }

void arraylist_push_front(ArrayList *list, void *data) {
  _arraylist_validate_insert(list);

  void *cpy = malloc(list->size);
  memcpy(cpy, data, list->size);

  for (int i = list->length; i > 0; i--) {
    list->data[i] = list->data[i - 1];
  }
  list->data[0] = cpy;

  list->length++;
}

void arraylist_push_back(ArrayList *list, void *data) {
  _arraylist_validate_insert(list);

  void *cpy = malloc(list->size);
  memcpy(cpy, data, list->size);

  list->data[list->length] = cpy;

  list->length++;
}

void *arraylist_pop_front(ArrayList *list) {
  if (list->length == 0)
    return NULL;

  void *data_ptr = list->data[0];
  for (int i = 0; i < list->length; i++) {
    list->data[i] = list->data[i + 1];
  }

  list->length--;

  return data_ptr;
}

void *arraylist_pop_back(ArrayList *list) {
  if (list->length == 0)
    return NULL;

  void *data_ptr = list->data[list->length - 1];
  list->data[list->length - 1] = NULL;

  list->length--;

  return data_ptr;
}

void *arraylist_get(ArrayList *list, int i) {
  if (i >= list->length)
    return NULL;

  void *cpy = malloc(list->size);
  memcpy(cpy, list->data[i], list->size);

  return cpy;
}

void arraylist_set(ArrayList *list, void *data, int i) {
  if (i >= list->length)
    return;

  memcpy(list->data[i], data, list->size);
}

void arraylist_swap(ArrayList *list, int i, int j) {
  void *swp = list->data[i];
  list->data[i] = list->data[j];
  list->data[j] = swp;
}

void arraylist_destroy(ArrayList *list) {
  free(list->data);
  free(list);
}

bool _arraylist_full(ArrayList *list) { return list->capacity == list->length; }

void _arraylist_resize(ArrayList *list) {
  list->capacity *= 1.5;
  list->data = realloc(list->data, list->capacity * list->size);
}

void _arraylist_validate_insert(ArrayList *list) {
  if (!_arraylist_full(list))
    return;
  _arraylist_resize(list);
}
