#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/list.h"

Node *add_node(Node *list, void *data) {

  Node *new_node = malloc(sizeof(Node));
  new_node -> data = data;  
  new_node -> next = list;

  return new_node; 
}

int search_list(void *data, Node *list, compFunction comp) {
  
  while(list) {
    if(comp(data, list -> data)) return 1;
    list = list -> next;
  }
  return 0;
}

Results *initialize_results() {
  Results *list = malloc(sizeof(Results));
  list -> actual = create_glist();
  list -> next = create_glist();

  return list;
}

void change_list(Results *words) {
  free(words->actual);
  words -> actual = words -> next;
  words -> next = create_glist();
}

Node *pass_node(Node *node) {
  Node *next_node = node -> next;
  free(node);
  return next_node;
}

Node *pass_destroy_node(Node *node, destFunction destroy) {
  Node *next_node = node->next;
  destroy(node->data);
  free(node);
  return next_node;
}

Node *node_create(void *data) {
  Node *new_node = malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

Glist *create_glist() {
  Glist *glist = malloc(sizeof(Glist));
  glist->first = NULL;
  glist->last = NULL;
  return glist;
}

Glist *glist_add_last(Glist *glist, void *data) {
  Node *new_node = node_create(data);
  if(glist->first) {
    glist->last->next = new_node;
    glist->last = new_node;
  } else {
    glist->first = new_node;
    glist->last = new_node;
  }
  return glist;
}

void glist_destroy(Glist *list) {
  Node *node = list->first;
  Node *next_node = NULL;
  while(node) {
    next_node = node->next;
    free(node);
    node = next_node;
  }
  free(list);
}

void results_destroy(Results *results) {
  glist_destroy(results->actual);
  glist_destroy(results->next);
  free(results);
}

void free_list(Node *list) {
  while(list) {
    Node *node = list;
    list = list -> next;
    free(node);
  }
  free(list);
}