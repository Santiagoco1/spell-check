#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/list.h"

Node *add_node(Node *list, Word *word) {

  Node *new_node = malloc(sizeof(Node));
  new_node -> word = word;  
  new_node -> next = list;

  return new_node;
}

int search_list(char word[], Node *list) {
  
  while(list) {
    if(strcmp(word, list->word->str) == 0) return 1;
    list = list -> next;
  }
  return 0;
}

List *initialize_list() {
  
  List *list = malloc(sizeof(List));
  list -> actual = NULL;
  list -> next = NULL;

  return list;
}

void change_list(List *words) {
  words -> actual = words -> next;
  words -> next = NULL;
}

Node *pass_node(Node *node) {
  Node *next_node = node -> next;
  free(node);
  return next_node;
}

void free_list(Node *list) {
  while(list) {
    Node *node = list;
    list = list -> next;
    free(node);
  }
  free(list);
}