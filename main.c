#include "prefix_tree.h"
#include <stdio.h>

void print_startup_text();
void print_help_text();

int main() {

  print_help_text();

  return 0;
}

void print_startup_text() {
  puts("-------------------------");
  puts("---- SCRABBLE SOLVER ----");
  puts("-------------------------\n\n");

  puts("Type \"help\" for more information");
  puts("Type \"quit\" when you're finished");
  puts("Otherwise, you can simply answer each question");
}

void print_help_text() {
  puts("When prompted about the number of letters, this is");
  puts("refering to the number of letters in the word you are");
  puts("trying to solve. For example, if your word was \"hello\" but");
  puts("all you knew about this word was that it was 5 letters, you");
  puts("would put 5\n");

  puts("When prompted about entering an alphabet, you can provide");
  puts("All the letters that are allowed to be used. If a letter");
  puts("Can be used multiple times, you must type that letter the");
  puts("amount of times you wish for it to be included. For example,");
  puts("The word \"hello\" has the alphabet \"ehllo\", the order of");
  puts("the letters doesn't matter, but you need to include duplicates");
  puts("If you want the letter to be used multiple times.");

  puts("When prompted about filling in knowledge about the word, you");
  puts("Can put the letters you know, as well as stars for what you don't");
  puts("know. For Example, if you know only the first and last letter of");
  puts("\"hello\", you would enter \"h***o\" as your knowledge of the letter");

  puts(
      "Also keep in mind that this application assumes only lowercase letters");
  puts("Numbers, uppercase letters, and any other character will break the "
       "program");
}
