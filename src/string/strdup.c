#include <stdlib.h>
#include <string.h>

char *strdup(const char *str) {
  char *dup = malloc(strlen(str) + 1);
  if (dup)
    strcpy(dup, str);
  return dup;
}
