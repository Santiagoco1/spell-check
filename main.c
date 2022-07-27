#include <stdio.h>
#include <stdlib.h>
#include "headers/dict.h"
#include "headers/check.h"
#include "headers/print.h"

int main(int argc, char **argv ) {
  if(argc == 3) {
    
    int amount = 0;
    Word **words = get_words(argv[1], &amount);

    HashTable *dictionary = create_dictionary(words, amount);
    free(words);

    Glist *corrections = check_text(argv[2], dictionary);
    free_hashtable(dictionary);

    print_text(corrections, argv[2]);
    free(corrections);
  }
  return 0;
}