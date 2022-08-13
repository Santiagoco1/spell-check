#ifndef __DICT_H__
#define __DICT_H__

#include "hash.h"

Word **get_words(char *path, int *amount, int *lengths);

HashTable *create_dictionary(Word **words, int amount);

#endif