#include <stdio.h>
#include <string.h>

int fputs(const char *restrict str, FILE *restrict stream) {
  return fwrite(str, 1, strlen(str), stream);
}
