#include <stdio.h>

int puts(const char *str) {
  if (stdout)
    return fputs(str, stdout) + fwrite("\n", 1, 1, stdout);
  return EOF;
}
