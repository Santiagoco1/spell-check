#include <stdio.h>
#include <stdlib.h>
#include "headers/dict.h"
#include "headers/check.h"
#include "headers/print.h"

#define LARGEST_WORD 35

int main(int argc, char **argv ) {
  if(argc == 3) {
    
    int amount = 0, lengths[LARGEST_WORD];
    for(int i = 0; i < LARGEST_WORD; i++) lengths[i] = 0;
    
    Word **words = get_words(argv[1], &amount, lengths);

    HashTable *dictionary = create_dictionary(words, amount);
    free(words);

    Glist *corrections = check_text(argv[2], dictionary, lengths);
    free_hashtable(dictionary);

    printf("Hasta aca llega\n");

    print_text(corrections, argv[2]);
    free(corrections);
  }
  return 0;
}