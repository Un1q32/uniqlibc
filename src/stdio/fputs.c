#include <stdio.h>
#include <string.h>

int fputs(const char *restrict str, FILE *restrict stream) {
  if (!str)
    return fputs("(null)", stream);
  return fwrite(str, 1, strlen(str), stream);
}
