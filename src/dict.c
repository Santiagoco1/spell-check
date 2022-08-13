#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/dict.h"

Word **get_words(char *path, int *amount, int *lengths) {

  int size = 1024, length;
  char string[35];
  Word **buf = malloc(sizeof(Word*) * size);

  FILE *file = fopen(path, "r");

  while(fscanf(file, "%s\n", string) == 1) {

    if((*amount) >= size) {
      size *= 2;
      buf = realloc(buf, sizeof(Word*) * size);
    }

    length = strlen(string);
    buf[(*amount)] = word_create(string, length);
    if(!lengths[length]) lengths[length]++;

    (*amount)++;
  }
  fclose(file);
  return buf;
}

HashTable *create_dictionary(Word **words, int amount) {

  HashTable *dictionary = initialize_hash_table(amount);

  for(int i = 0; i < amount; i++) {
    add_hashtable(dictionary, words[i]);
  }
  return dictionary;
}