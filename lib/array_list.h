#ifndef __HEADER_ARRAY_LIST
#define __HEADER_ARRAY_LIST

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ArrayList {
  void **data;
  int length, capacity;
  int size;
} ArrayList;

ArrayList *arraylist_init(int element_size);
ArrayList *arraylist_init_set_capacity(int element_size, int capacity);
int arraylist_length(ArrayList *list);
void arraylist_push_front(ArrayList *list, void *data);
void arraylist_push_back(ArrayList *list, void *data);
void *arraylist_pop_front(ArrayList *list, void *data);
void *arraylist_pop_back(ArrayList *list, void *data);

bool _arraylist_full(ArrayList *list);
void _arraylist_resize(ArrayList *list);
void _arraylist_validate_insert(ArrayList *list);

#endif
