#include <stdio.h>

char *gets(char *str) {
  if (stdin)
    return fgets(str, INT_MAX, stdin);
  return NULL;
}
