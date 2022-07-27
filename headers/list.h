#ifndef __LIST_H__
#define __LIST_H__

#include "word.h"

typedef struct _Node {
  void *data;
  struct _Node *next;
} Node;

typedef struct _Glist {
  Node *first;
  Node *last;
} Glist;

typedef struct _Results {
  Glist *actual;
  Glist *next;
} Results;

typedef int (*compFunction)(void *data1, void *data2);
typedef void (*destFunction)(void *data);

Node *add_node(Node *list, void *data);

int search_list(void *data, Node *list, compFunction comp);

Results *initialize_results();

void change_list(Results *words);

Node *pass_node(Node *node);

Node *pass_destroy_node(Node *node, destFunction destroy);

Node *node_create(void *data);

Glist *create_glist();

Glist *glist_add_last(Glist *glist, void *data);

void results_destroy(Results *results);

void glist_destroy(Glist *list);

void free_list(Node *list);

#endif