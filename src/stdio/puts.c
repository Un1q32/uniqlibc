#include <stdio.h>

int puts(const char *str) {
  if (stdout)
    return fputs(str, stdout) + fputs("\n", stdout);
  return EOF;
}
