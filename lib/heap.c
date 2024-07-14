#include "heap.h"
#include "array_list.h"

Heap *heap_init(int element_size, compare_func *compare) {
  return heap_init_set_capacity(element_size, compare, 10);
}

Heap *heap_init_set_capacity(int element_size, compare_func *compare,
                             int capacity) {
  Heap *heap = malloc(sizeof(Heap));
  heap->list = arraylist_init_set_capacity(element_size, capacity);
  heap->compare = compare;

  return heap;
}

int heap_length(Heap *heap) { return arraylist_length(heap->list); }

void heap_push(Heap *heap, void *data) {
  arraylist_push_back(heap->list, data);
  _heapify_up(heap);
}

void *heap_pop(Heap *heap) {
  int len = arraylist_length(heap->list);

  arraylist_swap(heap->list, 0, len - 1);
  void *elem = arraylist_pop_back(heap->list);
  _heapify_down(heap);

  return elem;
}

void heap_destroy(Heap *heap) {
  arraylist_destroy(heap->list);
  free(heap);
}

void _heapify_up(Heap *heap) {
  int i = arraylist_length(heap->list) - 1;

  while (i != 0) {
    int pi = (i - 1) / 2;

    void *elem = arraylist_get(heap->list, i);
    void *parent = arraylist_get(heap->list, pi);

    bool make_swap = heap->compare(elem, parent) > 0;

    free(elem);
    free(parent);

    if (!make_swap)
      return;

    arraylist_swap(heap->list, i, pi);
    i = pi;
  }
}

void _heapify_down(Heap *heap) {
  int i = 0;
  int li = 1, ri = 2;
  int len = arraylist_length(heap->list);

  while (li <= len - 1) {
    void *elem = arraylist_get(heap->list, i);
    void *left = arraylist_get(heap->list, li);

    if (li == len - 1) {
      if (heap->compare(left, elem) > 0) {
        arraylist_swap(heap->list, li, i);
      }

      free(elem);
      free(left);

      return;
    }

    void *right = arraylist_get(heap->list, ri);

    int mi = heap->compare(left, right) > 0 ? li : ri;
    void *mchild = (mi == li ? left : right);
    bool make_swap = heap->compare(mchild, elem) > 0;

    free(elem);
    free(left);
    free(right);

    if (!make_swap)
      return;

    arraylist_swap(heap->list, mi, i);
    i = mi;
    li = mi * 2 + 1;
    ri = mi * 2 + 2;
  }
}
