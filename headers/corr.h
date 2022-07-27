#ifndef __CORR_H__
#define __CORR_H__

#include "word.h"

typedef struct _Corr {
  char *word;
  int line;
  int count;
  char **suggs;
} Corr;

Corr *create_corr(char *str, int line, int count, char **suggestions);

void corr_fprintf(Corr *correction, FILE *path);

void corr_dest(void *correction);

#endif