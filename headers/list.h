#include "word.h"

typedef struct _Node {
  Word *word;
  struct _Node *next;
} Node;

typedef struct _List {
  Node *actual;
  Node *next;
} List;

Node *add_node(Node *list, Word *word);

int search_list(char word[], Node *list);

List *initialize_list();

void change_list(List *words);

Node *pass_node(Node *node);

void free_list(Node *list);