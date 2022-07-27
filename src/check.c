#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/check.h"

#define AMOUNT_SUGGESTIONS 5
#define AMOUNT_STEPS 3

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

void fifht_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {
  
  char *changed_word = malloc(sizeof(char) * word -> len + 2);

  for(int i = 0; (*count) < 5 && i < word -> len + 1; i++) {
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      insert_char(word, i, c, changed_word);
      if(search_hashtable(changed_word, dictionary)) {
        suggestions[(*count)] = malloc(sizeof(char) * word->len + 2);
        strcpy(suggestions[(*count)], changed_word);
        (*count)++;
      }
      if((*steps) > 1) {
        Word *word = create_word(changed_word);
        search_and_add(mods_table, mods_list, word);
      }
    }
  }
  free(changed_word);
}

void fourth_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {

  char *changed_word = word -> str;

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    char original_char = changed_word[i];
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      if(original_char != (char)c) {
        changed_word[i] = c;
        if(search_hashtable(changed_word, dictionary)) {
          suggestions[(*count)] = malloc(sizeof(char) * word->len + 1);
          strcpy(suggestions[(*count)], changed_word);
          (*count)++;
        }
        if((*steps) > 1) {
          Word *word = create_word(changed_word);
          search_and_add(mods_table, mods_list, word);
        }
      }
    }
    changed_word[i] = original_char;
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

void third_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {
  
  char changed_word[word -> len];

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    eliminate_char(word, i, changed_word);
    if(search_hashtable(changed_word, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word->len);
      strcpy(suggestions[(*count)], changed_word);
      (*count)++;
    }
    if((*steps) > 1) {
      Word *word = create_word(changed_word);
      search_and_add(mods_table, mods_list, word);
    }   
  }
}

void second_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char**suggestions, int *count, int *steps) {
  
  char *changed_word = word -> str;

  for(int i = 1; (*count) < 5 && i < word -> len; i++) {
    char c = changed_word[i];
    changed_word[i] = changed_word[i-1];
    changed_word[i-1] = c;
    if(search_hashtable(changed_word, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word -> len + 1);
      strcpy(suggestions[(*count)], changed_word);
      (*count)++;
    }
    if((*steps) > 1) {
      Word *word = create_word(changed_word);
      search_and_add(mods_table, mods_list, word);
    }
    changed_word[i-1] = changed_word[i];
    changed_word[i] = c;
  }
}

void split_str(Word *word, int i, char *word1, char *word2) {
  
  int a = 0, b = 0;

  for(int j = 0; j < word -> len; j++) {
    if(j < i) {
      word1[a] = word -> str[j];
      a++;
    }
    else {
      word2[b] = word -> str[j];
      b++;
    }
  }
  word1[a] = '\0';
  word2[b] = '\0';
}

void first_technique(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {
  
  char first_splited_word[word -> len + 1];
  char second_splited_word[word -> len + 1];

  for(int i = 1; (*count) < 5 && i < (word -> len); i++) {
    split_str(word, i, first_splited_word, second_splited_word);
    if(search_hashtable(first_splited_word, dictionary) && search_hashtable(second_splited_word, dictionary)) {
      suggestions[(*count)] = malloc(sizeof(char) * word->len + 2);
      strcpy(suggestions[(*count)], first_splited_word);
      suggestions[(*count)][i] = '-';
      suggestions[(*count)][i+1] = '\0';
      strcat(suggestions[(*count)], second_splited_word);
      (*count)++;
    }
  }
}

void apply_techniques(Word *word, Glist *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {

  void (*techniques[5])(Word*, Glist*, HashTable*, HashTable*, char**, int*, int*) = {first_technique, third_technique, second_technique, fourth_technique, fifht_technique};
  for(int i = 0; (*count) < 5 && i < 5; i++) {
    (*techniques[i])(word, mods_list, dictionary, mods_table, suggestions, count, steps);
  }
}

void _find_suggestions(Results *mods_list, HashTable *dictionary, HashTable *mods_table, char **suggestions, int *count, int *steps) {

  if((*steps) > 0 && (*count) < 5) {
    if(mods_list->actual->first) {
      apply_techniques(mods_list->actual->first->data, mods_list->next, dictionary, mods_table, suggestions, count, steps);
      mods_list->actual->first = pass_node(mods_list->actual->first);
      _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, steps);
    } else {
      (*steps)--;
      change_list(mods_list);
      _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, steps);
    }
  }
}

char **find_suggestions(char *str, int *count, HashTable *dictionary) {

  Word *word = create_word(str);
  int steps = AMOUNT_STEPS;
  char **suggestions = malloc(sizeof(char*) * AMOUNT_SUGGESTIONS);
  for(int i = 0; i < AMOUNT_SUGGESTIONS; i++) suggestions[i] = NULL;

  Results *mods_list = initialize_results();
  HashTable *mods_table = initialize_hash_table(100000);
  add_hashtable(mods_table, word);
  mods_list->actual = glist_add_last(mods_list->actual, word);

  _find_suggestions(mods_list, dictionary, mods_table, suggestions, count, &steps);
  
  results_destroy(mods_list);
  free_hashtable(mods_table);

  return suggestions;
}

Corr *check_word(char *str, int line, HashTable *dictionary) { 

  Corr *correction = NULL;
  if(!search_hashtable(str, dictionary)) {
    int count = 0;
    char **suggestions = find_suggestions(str, &count, dictionary);
    correction = create_corr(str, line, count, suggestions);
  }
  return correction; 
}

Glist *check_text(char *path, HashTable *dictionary) {

  int line = 1, i = 0;
  char c, str[35];
  Corr *correction;
  Glist *corrections = create_glist();
  FILE *file = fopen(path, "r");

  while(fscanf(file, "%c%*[:;,.?!]", &c) == 1) {
    if(c == ' ' || c == '\n') {
      str[i] = '\0';
      i = 0;
      if((correction = check_word(str, line, dictionary))) {
        corrections = glist_add_last(corrections, correction);
      }
      if(c == '\n') line++;
    } else {
      str[i] = c;
      i++;
    }
  }
  str[i] = '\0';
  if((correction = check_word(str, line, dictionary))) {
    corrections = glist_add_last(corrections, correction);
  }
  fclose(file);
  return corrections;
}