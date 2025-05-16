#include <stdio.h>

int fputc(int ch, FILE *stream) {
  if (fwrite(&ch, 1, 1, stream) != 1)
    return EOF;
  return ch;
}
