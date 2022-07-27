#ifndef __MOD_H__
#define __MOD_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _Mod {
  char *error;
  int *count;
  char **suggestions;
} Mod;

#endif