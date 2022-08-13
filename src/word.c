#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/word.h"

Word *word_create(char *string, int length) {

  Word *word = malloc(sizeof(Word));
  word->str = malloc(sizeof(char) * length+1);

  strcpy(word->str, string);
  word->len = length;

  return word;
}

int comp_word(void *string, void *word) {
  //printf("%s - %ld : %s - %d\n", (char*)string, strlen((char*)string), (char*)((Word*)word)->str,(int)((Word*)word)->len);
  if(strlen((char*)string) == (int)((Word*)word)->len) {
    for(int i = 0; i < (int)((Word*)word)->len; i++) {
      if(((char*)string)[i] != ((Word*)word)->str[i]) return 0;
    }
    return 1;
  }
  return 0;
  //return strcmp((char*)string, ((Word*)word) -> str) == 0;
}

void free_word(Word *word) {
  free(word -> str);
  free(word);
}