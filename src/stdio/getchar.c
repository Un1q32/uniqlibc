#include <stdio.h>

int getchar(void) {
  if (stdin)
    return getc(stdin);
  return EOF;
}
