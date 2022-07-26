#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _Word {
  char *str;
  int len;
} Word;

typedef struct _Node {
  Word *word;
  struct _Node *next;
} Node;

typedef struct _List {
  Node *actual;
  Node *next;
} List;

typedef struct _HashTable {
  Node **list;
  int len;
} HashTable;

Word *create_word(char str[]) {

  int length = strlen(str);
  Word *word = malloc(sizeof(Word));
  word -> str = malloc(sizeof(char) * length + 1);

  for(int i = 0; i < length; i++) {
    if((int)str[i] < 97) str[i] = (char)((int)str[i] + 32);
  }

  strcpy(word -> str, str);
  word -> len = length;

  return word;
}

Word **get_words(char *path, int *amount) {

  int size = 1024, length;
  char word[35];
  Word **buf = malloc(sizeof(Word*) * size);

  FILE *file = fopen(path, "r");

  while(fscanf(file, "%s\n", word) == 1) {

    if((*amount) >= size) {
      size *= 2;
      buf = realloc(buf, sizeof(Word*) * size);
    }
    
    buf[(*amount)] = create_word(word);

    (*amount)++;
  }
  fclose(file);
  return buf;
}

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

Node *add_node(Node *list, Word *word) {

  Node *new_node = malloc(sizeof(Node));
  new_node -> word = word;  
  new_node -> next = list;

  return new_node;
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

HashTable *create_dictionary(Word **words, int amount) {

  HashTable *dictionary = initialize_hash_table(amount);

  for(int i = 0; i < amount; i++) {
    add_hashtable(dictionary, words[i]);
  }
  return dictionary;
}

void show_list(Node *list) {
  while(list) {
    printf("%s\n", list->word->str);
    list = list->next;
  }
}

int search_list(char word[], Node *list) {
  
  while(list) {
    if(strcmp(word, list->word->str) == 0) return 1;
    list = list -> next;
  }
  return 0;
}

int search_hashtable(char word[], HashTable *dictionary) {
  
  int hash = hash_function(word, dictionary->len);
  return search_list(word, dictionary->list[hash]);
}

List *initialize_list() {
  
  List *list = malloc(sizeof(List));
  list -> actual = NULL;
  list -> next = NULL;

  return list;
}

List *change_list(List *words) {
  words -> actual = words -> next;
  words -> next = NULL;
}

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
  int j = 0;

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

Node *pass_node(Node *node) {
  Node *next_node = node -> next;
  free(node);
  return next_node;
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

void _find_suggestions(List *mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps) {
  
  if((*steps) > 0 && (*count) < 5) {
    if(mods_list -> actual) {
      apply_techniques(mods_list -> actual -> word, &(mods_list -> next), dictionary, mods_table, count, steps);
      mods_list -> actual = pass_node(mods_list -> actual);
      _find_suggestions(mods_list, dictionary, mods_table, count, steps);
    } else {
      (*steps)--;
      mods_list = change_list(mods_list);
      _find_suggestions(mods_list, dictionary, mods_table, count, steps);
    }
  } else {
    printf("\n\n");
  }
}

void free_list(Node *list) {
  while(list) {
    Node *node = list;
    list = list -> next;
    free(node);
  }
  free(list);
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

  int linea = 0;
  char aux[35];
  FILE *file = fopen(path, "r");

  while(fscanf(file, "%s", aux) == 1) {

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

int main(int argc, char **argv ) {
  if(argc == 3) {
    
    int amount = 0;
    Word **words = get_words(argv[1], &amount);

    HashTable *dictionary = create_dictionary(words, amount);
    free(words);

    check_text(argv[2], dictionary);

    free_hashtable(dictionary);
  }
  return 0;
}