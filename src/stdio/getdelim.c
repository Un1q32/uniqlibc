#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream) {
  if (lineptr == NULL || n == NULL || stream == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (*lineptr == NULL) {
    *lineptr = malloc(128);
    if (*lineptr == NULL)
      return -1;
    *n = 128;
  }

  size_t i = 0;
  int c;
  while ((c = fgetc(stream)) != EOF) {
    if (i >= *n) {
      size_t new_size = *n + 128;
      char *new_lineptr = realloc(*lineptr, new_size);
      if (new_lineptr == NULL)
        return -1;
      *lineptr = new_lineptr;
      *n = new_size;
    }

    (*lineptr)[i++] = c;
    if (c == delim)
      break;
  }

  if (i == 0)
    return -1;

  (*lineptr)[i] = '\0';
  return i;
}
