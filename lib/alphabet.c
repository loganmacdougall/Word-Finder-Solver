#include "alphabet.h"

Alphabet *alphabet_init(char *string) {
  Alphabet *alphabet = malloc(sizeof(*alphabet));

  memset(alphabet->alphabet, 0, 26 * sizeof(*alphabet->alphabet));

  return alphabet;
}

void alphabet_add_letter(Alphabet *alphabet, char letter) {
  alphabet->alphabet[letter - 'a']++;
}

void alphabet_sub_letter(Alphabet *alphabet, char letter) {
  alphabet->alphabet[letter - 'a']--;
}

bool alphabet_has_letter(Alphabet *alphabet, char letter) {
  return alphabet->alphabet[letter - 'a'] > 0;
}

void alphabet_destroy(Alphabet *alphabet) { free(alphabet); }
