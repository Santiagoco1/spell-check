#include <stdio.h>
#include <stdlib.h>
#include "headers/dict.h"
#include "headers/check.h"

void show_list(Node *list) {
  while(list) {
    printf("%s\n", list->word->str);
    list = list->next;
  }
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