#ifndef __HEADER_UNSCRABBLER
#define __HEADER_UNSCRABBLER

#include "alphabet.h"
#include "heap.h"
#include "prefix_tree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Unscrabbler {
  PrefixTree *tree;
  Alphabet *alphabet;
} Unscrabbler;

Unscrabbler *unscrabbler_init(char *dict_filename);
void unscrabbler_set_alphabet(Unscrabbler *solver, char *alphabet_str);
Queue *find_possible_words(Unscrabbler *solver, char *knowledge);
void unscrabbler_destroy(Unscrabbler *solver);

void _unscrabbler_find_possible_words_rec(PrefixTreeNode *node,
                                          Alphabet *alphabet, char *knowledge,
                                          Heap *word_sorter, char *word,
                                          int wordlen);

#endif
