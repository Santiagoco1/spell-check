#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/word.h"

Word *create_word(char str[]) {

  int length = strlen(str);
  Word *word = malloc(sizeof(Word));
  word -> str = malloc(sizeof(char) * length + 1);

  for(int i = 0; i < length; i++) {
    if((int)str[i] < 97) str[i] = (char)((int)str[i] + 32);
  }

  strcpy(word -> str, str);
  word -> len = length;

  return word;
}