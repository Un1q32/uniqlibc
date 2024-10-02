#include <stdio.h>

int putchar(int ch) {
  if (stdout)
    return fputc(ch, stdout);
  return EOF;
}
