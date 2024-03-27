#ifndef __HEADER_QUEUE
#define __HEADER_QUEUE

#include "linked_list.h"

typedef LinkedList Queue;

Queue *queue_init(int element_size);
int queue_length(Queue *queue);
void queue_push(Queue *queue, void *data);
void *queue_pop(Queue *queue);
void queue_destroy(Queue *queue);

#endif
