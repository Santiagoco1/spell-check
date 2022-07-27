#ifndef __HASH_H__
#define __HASH_H__

#include "list.h"

typedef struct _HashTable {
  Node **list;
  int len;
} HashTable;

HashTable *initialize_hash_table(int amount);

int hash_function (char *word, int amount);

void add_hashtable (HashTable *dictionary, Word *word);

int _search_and_add(Node *list, Word *word);

void search_and_add(HashTable *words_table, Node **words, Word *word);

int search_hashtable(char *word, HashTable *dictionary);

void free_hashtable(HashTable *hashTable);

#endif