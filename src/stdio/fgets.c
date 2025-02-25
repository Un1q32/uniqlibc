#include <stdio.h>

char *fgets(char *restrict str, int size, FILE *restrict stream) {
  int i = 0;
  while (i < size - 1) {
    int c = fgetc(stream);
    if (c == EOF) {
      if (i == 0)
        return NULL;
      break;
    }
    str[i] = c;
    if (c == '\n')
      break;
    i++;
  }
  str[i + 1] = '\0';
  return str;
}
