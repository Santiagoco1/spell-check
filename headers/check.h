#ifndef __CHECK_H__
#define __CHECK_H__

#include "hash.h"
#include "list.h"
#include "corr.h"

void insert_char(Word *word, int i, char c, char *aux);

void fifht_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void fourth_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void eliminate_char(Word *word, int i, char *aux);

void third_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void second_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void split_str(Word *word, int i, char *word1, char *word2, char* splited_str);

void first_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void apply_techniques(Word *mods_list, Glist *list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

void _find_suggestions(Results *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths);

char **find_suggestions(Word *word, int *count, HashTable *dictionary, int *lengths);

Corr *check_word(char *str, int length, int line, HashTable *dictionary, int *lengths);

Glist *check_text(char *path, HashTable *dictionary, int *lengths);

#endif