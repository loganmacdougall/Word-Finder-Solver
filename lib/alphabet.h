#ifndef __HEADER_ALPHABET
#define __HEADER_ALPHABET

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Alphabet {
  unsigned char alphabet[26];
} Alphabet;

Alphabet *alphabet_init(char *string);
void alphabet_add_letter(Alphabet *alphabet, char letter);
void alphabet_sub_letter(Alphabet *alphabet, char letter);
bool alphabet_has_letter(Alphabet *alphabet, char letter);
void alphabet_destroy(Alphabet *alphabet);

#endif
