#ifndef __WORD_H__
#define __WORD_H__

typedef struct _Word {
  char *str;
  int len;
} Word;

Word *create_word(char *str);

int comp_word(void *string, void *word);

void free_word(Word *word);

#endif