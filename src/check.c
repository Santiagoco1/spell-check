#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/check.h"

#define SUGGESTIONS 5
#define STEPS 3

void insert_char(Word *word, int i, char c, char *aux) {

  int j = 0, q = 0;
  for(; j < word -> len + 1; j++) {
    if(j == i) {
      aux[j] = (char)c;
    } else {
      aux[j] = word -> str[q];
      q++;
    }
  }
  aux[j] = '\0';
}

int in_range(int length, int *lengths) {
  if(lengths[length]) return 1;
  for(int i = 1; i <= STEPS; i++) {
    if(lengths[length+i]) return 1;
    if(lengths[length-i]) return 1;
  }
  return 0;
}

void fifht_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {
  
  char *changed_str = malloc(sizeof(char) * word->len+2);

  for(int i = 0; (*count) < 5 && i < word -> len + 1; i++) {
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      insert_char(word, i, c, changed_str);
      if(search_hashtable(changed_str, dictionary)) {
        suggestions[(*count)] = malloc(sizeof(char) * word->len + 2);
        strcpy(suggestions[(*count)], changed_str);
        (*count)++;
      }
      if((*steps) > 1) {
        Word *changed_word = word_create(changed_str, word->len+1);
        search_and_add(mods_table, mods_list, changed_word);
      }
    }
  }
}

void fourth_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {

  char *changed_string = word -> str;

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    char original_char = changed_string[i];
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      if(original_char != (char)c) {
        changed_string[i] = c;
        if(search_hashtable(changed_string, dictionary)) {
          suggestions[(*count)] = malloc(sizeof(char) * word->len + 1);
          strcpy(suggestions[(*count)], changed_string);
          (*count)++;
        }
        if((*steps) > 1) {
          Word *changed_word = word_create(changed_string, strlen(word->str));
          search_and_add(mods_table, mods_list, changed_word);
        }
      }
    }
    changed_string[i] = original_char;
  }
}

void eliminate_char(Word *word, int i, char *aux) {
  
  int j = 0;

  for(int p = 0; p < word -> len; p++) {
    if(p != i) {
      aux[j] = word -> str[p];
      j++;
    }
  }  
  aux[j] = '\0';
}

void third_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {
  
  char *changed_string = malloc(sizeof(char) * word->len);

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    eliminate_char(word, i, changed_string);
    if(search_hashtable(changed_string, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word->len);
      strcpy(suggestions[(*count)], changed_string);
      (*count)++;
    }
    if((*steps) > 1) {
      Word *changed_word = word_create(changed_string, word->len-1);
      search_and_add(mods_table, mods_list, changed_word);
    }   
  }
}

void second_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char**suggestions, int *count, int *steps, int *lengths) {
  
  char *changed_string = word->str;

  for(int i = 1; (*count) < 5 && i < word -> len; i++) {
    char c = changed_string[i];
    changed_string[i] = changed_string[i-1];
    changed_string[i-1] = c;
    if(search_hashtable(changed_string, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word -> len + 1);
      strcpy(suggestions[(*count)], changed_string);
      (*count)++;
    }
    if((*steps) > 1) {
      Word *changed_word = word_create(changed_string, word->len);
      search_and_add(mods_table, mods_list, changed_word);
    }
    changed_string[i-1] = changed_string[i];
    changed_string[i] = c;
  }
}

void split_str(Word *word, int i, char *word1, char *word2, char *splited_str) {
  
  int a = 0, b = 0, c = 0;

  for(int j = 0; j < word -> len; j++) {
    if(j < i) {
      word1[a] = word -> str[j];
      a++;
    } else {
      if(j == i) {
        splited_str[c] = '-';
        c++;
      }
      word2[b] = word -> str[j];
      b++;
    }
    splited_str[c] = word->str[j];
    c++;
  }
  word1[a] = '\0';
  word2[b] = '\0';
  splited_str[c] = '\0';
}

void first_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {
  
  char *first_splited_word = malloc(sizeof(char) * word->len+1);
  char *second_splited_word = malloc(sizeof(char) * word->len+1);
  char *splited_str = malloc(sizeof(char) * word->len+2);

  for(int i = 1; (*count) < 5 && i < (word -> len); i++) {
    split_str(word, i, first_splited_word, second_splited_word, splited_str);
    if(search_hashtable(first_splited_word, dictionary) && search_hashtable(second_splited_word, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word->len + 2);
      strcpy(suggestions[(*count)], splited_str);
      (*count)++;
    }
  }
}

void apply_techniques(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {

  void (*techniques[5])(Word*, Glist*, HashTable*, HashTable*, char**, int*, int*, int*) = {first_technique, third_technique, fourth_technique, second_technique, fifht_technique};
  for(int i = 0; (*count) < 5 && i < 5; i++) {
    (*techniques[i])(word, mods_list, dictionary, mods_table, suggestions, count, steps, lengths);
  }
}

void _find_suggestions(Results *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps, int *lengths) {

  if((*steps) > 0 && (*count) < 5) {
    if(mods_list->actual->first) {
      apply_techniques(mods_list->actual->first->data, mods_list->next, dictionary, mods_table, suggestions, count, steps, lengths);
      mods_list->actual->first = pass_node(mods_list->actual->first);
      _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, steps, lengths);
    } else {
      (*steps)--;
      change_list(mods_list);
      _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, steps, lengths);
    }
  }
}

char **find_suggestions(Word *word, int *count, HashTable *dictionary, int *lengths) {

  int steps = STEPS;
  char **suggestions = malloc(sizeof(char*) * SUGGESTIONS);
  for(int i = 0; i < SUGGESTIONS; i++) suggestions[i] = NULL;

  Results *mods_list = initialize_results();
  HashTable *mods_table = initialize_hash_table(10000);
  add_hashtable(mods_table, word);
  mods_list->actual = glist_add_last(mods_list->actual, word);

  _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, &steps, lengths);
  
  results_destroy(mods_list);
  free_hashtable(mods_table);

  return suggestions;
}

Corr *check_word(char *str, int length, int line, HashTable *dictionary, int *lengths) { 
  Corr *correction = NULL;
  if(!search_hashtable(str, dictionary)) {
    Word *word = word_create(str, length);
    int count = 0;
    char **suggestions = NULL;
    if(in_range(length, lengths)) {
      suggestions = find_suggestions(word, &count, dictionary, lengths);
    }
    correction = create_corr(str, line, count, suggestions);
  }

  return correction; 
}

Glist *check_text(char *path, HashTable *dictionary, int *lengths) {

  int line = 1, i = 0;
  char c, str[35];
  Corr *correction;
  Glist *corrections = create_glist();
  FILE *file = fopen(path, "r");

  while(fscanf(file, "%c%*[:;,.?!]", &c) == 1) {
    if(c == ' ' || c == '\n') {
      str[i] = '\0';

      for(int j = 0; j < i; j++) {
        str[j] = tolower(str[j]);
      }

      if((correction = check_word(str, i, line, dictionary, lengths))) {
        corrections = glist_add_last(corrections, correction);
      }
      i = 0;
      if(c == '\n') line++;
    } else {
      str[i] = c;
      i++;
    }
  }
  str[i] = '\0';
  if((correction = check_word(str, i, line, dictionary, lengths))) {
    corrections = glist_add_last(corrections, correction);
  }
  fclose(file);
  return corrections;
}