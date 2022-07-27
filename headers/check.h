#ifndef __CHECK_H__
#define __CHECK_H__

#include "hash.h"
#include "list.h"
#include "corr.h"

void insert_char(Word *word, int i, char c, char *aux);

void fifht_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void fourth_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void eliminate_char(Word *word, int i, char *aux);

void third_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void second_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void split_str(Word *word, int i, char *word1, char *word2);

void first_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void apply_techniques(Word *mods_list, Glist *list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

void _find_suggestions(Results *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps);

char **find_suggestions(char *str, int *count, HashTable *dictionary);

Corr *check_word(char *str, int line, HashTable *dictionary);

Glist *check_text(char *path, HashTable *dictionary);

#endif