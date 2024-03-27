#ifndef __HEADER_PREFIX_TREE
#define __HEADER_PREFIX_TREE

#define NUM_OF_LETTERS 26

#include <stdbool.h>
#include <stdlib.h>

typedef struct _PrefixTreeNode {
  struct _PrefixTreeNode **nextLetters;
  bool isWord;
} PrefixTreeNode;

typedef struct _PrefixTree {
  PrefixTreeNode *head;
} PrefixTree;

PrefixTree *prefix_tree_init();
void prefix_tree_add_word(PrefixTree *tree, char *word);
bool prefix_tree_has_word(PrefixTree *tree, char *word);
void prefix_tree_destroy(PrefixTree *tree);

PrefixTreeNode *_prefix_tree_init_node();
void _prefix_tree_destroy_node(PrefixTreeNode *node);

int _prefix_tree_letter_index(char letter);

#endif
