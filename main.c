#include "lib/heap.h"
#include "lib/queue.h"
#include "lib/unscrabbler.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define QUIT_CODE 1

void get_alphabet(char *buffer, bool allow_use_previous);
void get_knowledge(char *buffer);
void print_startup_text();
void print_help_text();

int main() {

  // I'm not currently implementing anything to
  // prevent buffer overflow attacks for this code.
  char alphabetBuffer[200];
  char knowledgeBuffer[50];
  Unscrabbler *solver = unscrabbler_init("dictionary_plus_analysis.txt");

  print_startup_text();

  while (1) {
    get_alphabet(alphabetBuffer, solver->alphabet != NULL);
    if (alphabetBuffer[0] == QUIT_CODE)
      break;

    if (alphabetBuffer[0] != '^' || solver->alphabet == NULL)
      unscrabbler_set_alphabet(solver, alphabetBuffer);

    get_knowledge(knowledgeBuffer);
    if (knowledgeBuffer[0] == QUIT_CODE)
      break;

    Heap *found = find_possible_words(solver, knowledgeBuffer);

    if (heap_length(found) == 0) {
      puts("\nNo solutions found");
    } else {
      puts("\n-- Solutions --");
    }

    static char *white_bold = "\e[1;97m";
    static char *default_color = "\e[0m";
    static char *black_bold = "\e[1;90m";

    while (heap_length(found) != 0) {
      WeightedWord *ww = heap_pop(found);

      char *color;
      if (ww->weight > 2000000)
        color = white_bold;
      else if (ww->weight < 350000)
        color = black_bold;
      else
        color = default_color;

      printf("  %s%s\n", color, ww->word);
      free(ww->word);
      free(ww);
    }
    puts("\e[0m");

    heap_destroy(found);
  }

  unscrabbler_destroy(solver);

  return 0;
}

void get_alphabet(char *buffer, bool allow_use_previous) {
  printf("Provide an alphabet: ");
  scanf("%s", buffer);

  if (strncmp(buffer, "!help", 5) == 0) {
    print_help_text();
    return get_alphabet(buffer, allow_use_previous);
  }

  if (strncmp(buffer, "!quit", 5) == 0) {
    buffer[0] = QUIT_CODE;
    return;
  }

  if (buffer[0] == '^' && allow_use_previous)
    return;

  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
    } else if (buffer[i] < 'a' || buffer[i] > 'z') {
      printf("Character %c is invalid\n", buffer[i]);
      return get_alphabet(buffer, allow_use_previous);
    }
  }
}

void get_knowledge(char *buffer) {
  printf("Provide knowledge: ");
  scanf("%s", buffer);

  if (strncmp(buffer, "!help", 5) == 0) {
    print_help_text();
    return get_knowledge(buffer);
  }

  if (strncmp(buffer, "!quit", 5) == 0) {
    buffer[0] = QUIT_CODE;
    return;
  }

  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
    } else if (buffer[i] != '*' && (buffer[i] < 'a' || buffer[i] > 'z')) {
      printf("Character %c is invalid\n", buffer[i]);
      return get_knowledge(buffer);
    }
  }
}

void print_startup_text() {
  puts("-------------------------");
  puts("---- SCRABBLE SOLVER ----");
  puts("-------------------------\n\n");

  puts("Type \"!help\" for more information");
  puts("Type \"!quit\" when you're finished\n");
}

void print_help_text() {
  puts("When prompted about entering an alphabet, you can provide");
  puts("All the letters that are allowed to be used. If a letter");
  puts("Can be used multiple times, you must type that letter the");
  puts("amount of times you wish for it to be included. For example,");
  puts("The word \"hello\" has the alphabet \"ehllo\", the order of");
  puts("the letters doesn't matter, but you need to include duplicates");
  puts("If you want the letter to be used multiple times.\n");

  puts("If you want to use the same alphabet that you used last time instead");
  puts("of typing it over again, you can type the alphabet as '^' instead of");
  puts("a valid new alphabet\n");

  puts("When prompted about filling in knowledge about the word, you");
  puts("Can put the letters you know, as well as stars for what you don't");
  puts("know. For Example, if you know only the first and last letter of");
  puts(
      "\"hello\", you would enter \"h***o\" as your knowledge of the letter\n");

  puts("Also keep in mind that this application assumes only lowercase");
  puts("letters. Numbers, uppercase letters, and any other character");
  puts("will break the program.\n");
}
