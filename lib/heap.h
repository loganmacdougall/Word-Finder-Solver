#ifndef __HEADER_HEAP
#define __HEADER_HEAP

#include "array_list.h"

typedef int compare_func(void *a, void *b);
typedef struct _Heap {
  ArrayList *list;
  // positive: ..., a, ..., b, ...
  // negative: ..., b, ..., a, ...
  // zero: equal/undefined
  compare_func *compare;
} Heap;

Heap *heap_init(int element_size, compare_func *compare);
Heap *heap_init_set_capacity(int element_size, compare_func *compare,
                             int capacity);
int heap_length(Heap *heap);
void heap_push(Heap *heap, void *data);
void *heap_pop(Heap *heap);
void heap_destroy(Heap *heap);

void _heapify_up(Heap *heap);
void _heapify_down(Heap *heap);

#endif
