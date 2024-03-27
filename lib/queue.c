#include "queue.h"

Queue *queue_init(int element_size) { return linkedlist_init(element_size); }

int queue_length(Queue *queue) { return linkedlist_length(queue); }

void queue_push(Queue *queue, void *data) { linkedlist_push_back(queue, data); }

void *queue_pop(Queue *queue) { return linkedlist_pop_front(queue); }

void queue_destroy(Queue *queue) { linkedlist_destroy(queue); }
