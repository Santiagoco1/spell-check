#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"

HashTable *initialize_hash_table(int amount) {

  HashTable *hash_table = malloc(sizeof(HashTable));
  hash_table->list = malloc(sizeof(Node*) * amount);

  for(int i = 0; i < amount; i++) {
    hash_table->list[i] = NULL;
  }
  hash_table->len = amount;

  return hash_table;
}

int hash_function (char *word, int amount) {

  unsigned hashval;
  for (hashval = 0; *word != '\0'; ++word) {
    hashval = *word + 31 * hashval;
  }
  return hashval % amount;
}

void add_hashtable (HashTable *dictionary, Word *word) {

  int hash = hash_function(word->str, dictionary->len);
  dictionary->list[hash] = add_node(dictionary->list[hash], word);
}

int _search_and_add(Node *list, Word *word) {
  while(list) {
    if(strcmp(list -> word -> str, word -> str) == 0) return 0;
    list = list -> next;
  }
  return 1;
}

void search_and_add(HashTable *words_table, Node **words, Word *word) {
  int hash = hash_function(word -> str, words_table -> len);
  if(_search_and_add(words_table -> list[hash], word)) {
    words_table -> list[hash] = add_node(words_table->list[hash], word);
    (*words) = add_node((*words), word);
  } else {
    free(word -> str);
    free(word);
  }
}

int search_hashtable(char word[], HashTable *dictionary) {
  
  int hash = hash_function(word, dictionary->len);
  return search_list(word, dictionary->list[hash]);
}

void free_hashtable(HashTable *hashTable) {
  for(int i = 0; i < hashTable -> len; i++) {
    Node *list = hashTable -> list[i];
    while(list) {
      Node *node = list;
      list = list -> next;
      free(node -> word -> str);
      free(node -> word);
      free(node);
    }
    free(list);
  }
  free(hashTable -> list);
  free(hashTable);
}