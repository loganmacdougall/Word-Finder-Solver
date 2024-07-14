#include "unscrabbler.h"
#include "alphabet.h"
#include "heap.h"
#include "prefix_tree.h"

int compare_weighted_words(void *a, void *b) {
  WeightedWord *aw = (WeightedWord *)a;
  WeightedWord *bw = (WeightedWord *)b;
  long r = (long)aw->weight - (long)bw->weight;
  if (r > 0)
    return 1;
  if (r < 0)
    return -1;
  return 0;
}

Unscrabbler *unscrabbler_init(char *dict_filename) {
  static char buffer[60];

  Unscrabbler *solver = malloc(sizeof(*solver));
  solver->tree = prefix_tree_init();
  solver->alphabet = NULL;

  FILE *dict_file = fopen(dict_filename, "r");
  if (dict_file == NULL)
    return NULL;

  while (fgets(buffer, 60, dict_file) != NULL) {
    int i = 0;

    for (; buffer[i] != '\t'; i++)
      ;
    buffer[i] = '\n';

    unsigned long value = atol(&buffer[i + 1]);
    prefix_tree_add_word(solver->tree, buffer, value);
  }

  fclose(dict_file);

  return solver;
}

void unscrabbler_set_alphabet(Unscrabbler *solver, char *alphabet_str) {
  if (solver->alphabet != NULL)
    free(solver->alphabet);
  solver->alphabet = alphabet_init(alphabet_str);
}

Heap *find_possible_words(Unscrabbler *solver, char *knowledge) {
  Heap *word_sorter = heap_init(sizeof(WeightedWord), compare_weighted_words);
  char *word = calloc(strlen(knowledge) + 1, sizeof(*word));

  _unscrabbler_find_possible_words_rec(solver->tree->head, solver->alphabet,
                                       knowledge, word_sorter, word, 0);

  free(word);

  return word_sorter;
}

void unscrabbler_destroy(Unscrabbler *solver) {
  prefix_tree_destroy(solver->tree);
  alphabet_destroy(solver->alphabet);
  free(solver);
}

void _unscrabbler_find_possible_words_rec(PrefixTreeNode *node,
                                          Alphabet *alphabet, char *knowledge,
                                          Heap *word_sorter, char *word,
                                          int wordlen) {
  if (knowledge[0] == '\0') {
    if (node->value > 0) {
      WeightedWord ww;
      ww.word = malloc(sizeof(char) * (wordlen + 1));
      strcpy(ww.word, word);
      ww.weight = node->value;
      heap_push(word_sorter, &ww);
    }
    return;
  }

  if (knowledge[0] == '*') {
    for (int i = 0; i < NUM_OF_LETTERS; i++) {
      char letter = 'a' + i;
      if (!alphabet_has_letter(alphabet, letter))
        continue;
      if (node->nextLetters[i] == NULL)
        continue;
      alphabet_sub_letter(alphabet, letter);
      word[wordlen] = letter;
      _unscrabbler_find_possible_words_rec(node->nextLetters[i], alphabet,
                                           &knowledge[1], word_sorter, word,
                                           wordlen + 1);
      alphabet_add_letter(alphabet, letter);
    }
    return;
  }

  char letter = knowledge[0];
  if (!alphabet_has_letter(alphabet, letter))
    return;
  if (node->nextLetters[letter - 'a'] == NULL)
    return;
  alphabet_sub_letter(alphabet, letter);
  word[wordlen] = letter;
  _unscrabbler_find_possible_words_rec(node->nextLetters[letter - 'a'],
                                       alphabet, &knowledge[1], word_sorter,
                                       word, wordlen + 1);
  alphabet_add_letter(alphabet, letter);
}
