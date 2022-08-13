#ifndef __WORD_H__
#define __WORD_H__

typedef struct _Word {
  char *str;
  int len;
} Word;

Word *word_create(char *string, int length);

int comp_word(void *string, void *word);

void free_word(Word *word);

#endif