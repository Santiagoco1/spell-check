#include "hash.h"

Word **get_words(char *path, int *amount);

HashTable *create_dictionary(Word **words, int amount);