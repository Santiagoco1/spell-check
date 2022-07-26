#include <stdio.h>
#include <stdlib.h>
#include "../headers/hash.h"

void insert_char(Word *word, int i, char c, char aux[]) {

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

void fifht_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  char *changed_word = malloc(sizeof(char) * word -> len + 2);

  for(int i = 0; (*count) < 5 && i < word -> len + 1; i++) {
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      insert_char(word, i, c, changed_word);
      if(search_hashtable(changed_word, dictionary)) {
        printf("%s, ", changed_word);
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

void fourth_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {

  char *changed_word = word -> str;

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    char original_char = changed_word[i];
    for(int c = 97; (*count) < 5 && c < 123; c++) {
      if(original_char != (char)c) {
        changed_word[i] = c;
        if(search_hashtable(changed_word, dictionary)) {
          printf("%s, ", changed_word);
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

void eliminate_char(Word *word, int i, char aux[]) {
  
  int j = 0;

  for(int p = 0; p < word -> len; p++) {
    if(p != i) {
      aux[j] = word -> str[p];
      j++;
    }
  }  
  aux[j] = '\0';
}

void third_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  char changed_word[word -> len];

  for(int i = 0; (*count) < 5 && i < word -> len; i++) {
    eliminate_char(word, i, changed_word);
    if(search_hashtable(changed_word, dictionary)) {
      printf("%s, ", changed_word);
      (*count)++;
    }
    if((*steps) > 1) {
      Word *word = create_word(changed_word);
      search_and_add(mods_table, mods_list, word);
    }   
  }
}

void second_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  char *changed_word = word -> str;

  for(int i = 1; (*count) < 5 && i < word -> len; i++) {
    char c = changed_word[i];
    changed_word[i] = changed_word[i-1];
    changed_word[i-1] = c;
    if(search_hashtable(changed_word, dictionary)) {
      printf("%s, ", changed_word);
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

void split_str(Word *word, int i, char word1[], char word2[]) {
  
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

void first_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  char first_splited_word[word -> len + 1];
  char second_splited_word[word -> len + 1];

  for(int i = 1; (*count) < 5 && i < (word -> len); i++) {
    split_str(word, i, first_splited_word, second_splited_word);
    if(search_hashtable(first_splited_word, dictionary) && search_hashtable(second_splited_word, dictionary)) {
      printf("%s - %s, ", first_splited_word, second_splited_word);
      (*count)++;
    }
  }
}

void apply_techniques(Word *mods_list, Node **list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {

  void (*techniques[5])(Word*, Node**, HashTable*, HashTable*, int*, int*) = {first_technique, third_technique, second_technique, fourth_technique, fifht_technique};
  for(int i = 0; (*count) < 5 && i < 5; i++) {
    (*techniques[i])(mods_list, list, dictionary, mods_table, count, steps);
  }
}

void _find_suggestions(List *mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  if((*steps) > 0 && (*count) < 5) {
    if(mods_list -> actual) {
      apply_techniques(mods_list -> actual -> word, &(mods_list -> next), dictionary, mods_table, count, steps);
      mods_list -> actual = pass_node(mods_list -> actual);
      _find_suggestions(mods_list, dictionary, mods_table, count, steps);
    } else {
      (*steps)--;
      change_list(mods_list);
      _find_suggestions(mods_list, dictionary, mods_table, count, steps);
    }
  } else {
    printf("\n\n");
  }
}

void find_suggestions(Word *word, HashTable *dictionary) {
  
  int steps = 3, count = 0;
  List *mods_list = initialize_list();
  HashTable *mods_table = initialize_hash_table(100000);
  add_hashtable(mods_table, word);
  mods_list -> actual = add_node(mods_list -> actual, word);
  
  _find_suggestions(mods_list, dictionary, mods_table, &count, &steps);
  free_list(mods_list -> actual);
  free_list(mods_list -> next);
  free(mods_list);
  free_hashtable(mods_table);
}

void check_text(char *path, HashTable *dictionary) {

  char aux[35];
  FILE *file = fopen(path, "r");

  while(fscanf(file, "%[^,.\n ]%*[,.\n ]", aux) == 1) {

    Word *word = create_word(aux);
    if(search_hashtable(word -> str, dictionary) == 0) {
      printf("Linea N, '%s' no esta en el diccionario.\nQuizas quiso decir: ", word -> str);
      find_suggestions(word, dictionary);
    } else {
      free(word -> str);
      free(word);
    }
  }
  fclose(file);
}