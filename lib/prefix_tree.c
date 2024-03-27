#include "prefix_tree.h"

PrefixTree *prefix_tree_init() {
  PrefixTree *tree = malloc(sizeof(*tree));

  tree->head = _prefix_tree_init_node();

  return tree;
}

void prefix_tree_add_word(PrefixTree *tree, char *word) {
  PrefixTreeNode *node = tree->head;
  char *restOfWord = word;
  int nextLetterIndex = -1;

  while ((nextLetterIndex = _prefix_tree_letter_index(*restOfWord)) != -1) {
    if (node->nextLetters[nextLetterIndex] == NULL) {
      node->nextLetters[nextLetterIndex] = _prefix_tree_init_node();
    }
    node = node->nextLetters[nextLetterIndex];
    restOfWord = &restOfWord[1];
  }

  node->isWord = true;
}

bool prefix_tree_has_word(PrefixTree *tree, char *word) {
  PrefixTreeNode *node = tree->head;
  char *restOfWord = word;
  int nextLetterIndex = -1;

  while ((nextLetterIndex = _prefix_tree_letter_index(*restOfWord)) != -1) {
    if (node->nextLetters[nextLetterIndex] == NULL) {
      return false;
    }
    node = node->nextLetters[nextLetterIndex];
    restOfWord = &restOfWord[1];
  }

  return node->isWord;
}

void prefix_tree_destroy(PrefixTree *tree) {
  _prefix_tree_destroy_node(tree->head);
  free(tree);
}

PrefixTreeNode *_prefix_tree_init_node() {
  PrefixTreeNode *node = malloc(sizeof(*node));

  node->isWord = false;
  // Calloc initilzies memory to all 0s
  node->nextLetters = calloc(25, sizeof(&node));

  return node;
}

void _prefix_tree_destroy_node(PrefixTreeNode *node) {
  for (int i = 0; i < NUM_OF_LETTERS; i++) {
    PrefixTreeNode *possibleNode = node->nextLetters[i];
    if (possibleNode != NULL)
      _prefix_tree_destroy_node(possibleNode);
  }

  free(node->nextLetters);
  free(node);
}

int _prefix_tree_letter_index(char letter) {
  if (letter < 'a' || letter > 'z')
    return -1;
  return letter - 'a';
}
