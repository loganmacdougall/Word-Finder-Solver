#include "unscrabbler.h"
#include "alphabet.h"
#include "prefix_tree.h"

Unscrabbler *unscrabbler_init(char *dict_filename) {
  static char buffer[50];

  Unscrabbler *solver = malloc(sizeof(*solver));
  solver->tree = prefix_tree_init();
  solver->alphabet = NULL;

  FILE *dict_file = fopen(dict_filename, "r");
  if (dict_file == NULL)
    return NULL;

  while (fgets(buffer, 50, dict_file) != NULL) {
    prefix_tree_add_word(solver->tree, buffer);
  }

  return solver;
}

void unscrabbler_set_alphabet(Unscrabbler *solver, char *alphabet_str) {
  if (solver->alphabet != NULL)
    free(solver->alphabet);
  solver->alphabet = alphabet_init(alphabet_str);
}

Queue *find_possible_words(Unscrabbler *solver, char *knowledge) {
  Queue *found = queue_init(sizeof(char *));
  char *word = calloc(strlen(knowledge) + 1, sizeof(*word));

  return found;
}

void unscrabbler_destroy(Unscrabbler *solver) {
  prefix_tree_destroy(solver->tree);
  alphabet_destroy(solver->alphabet);
  free(solver);
}

void _unscrabbler_find_possible_words_rec(PrefixTreeNode *node,
                                          Alphabet *alphabet, char *knowledge,
                                          Queue *found, char *word,
                                          int wordlen) {
  if (knowledge[0] == '\0') {
    if (node->isWord) {
      char *word_cpy = _unscrabbler_strrev(word, wordlen);
      strcpy(word_cpy, word);
      queue_push(found, word_cpy);
    }
    return;
  }

  for (int i = 0; i < NUM_OF_LETTERS; i++) {
    char letter = 'a' + i;
    if (alphabet_has_letter(alphabet, letter)) {
      alphabet_sub_letter(alphabet, letter);
      word[wordlen] = letter;
      _unscrabbler_find_possible_words_rec(node->nextLetters[i], alphabet,
                                           &knowledge[1], found, word,
                                           wordlen + 1);
      alphabet_add_letter(alphabet, letter);
    }
  }
}

char *_unscrabbler_strrev(char *str, int len) {
  char *rev = malloc(sizeof(char) * (len + 1));
  rev[len] = '\0';
  for (int i = 0; i < len; i++) {
    rev[i] = str[len - i - 1];
  }
  return rev;
}
