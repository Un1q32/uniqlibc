#include <stdio.h>

int fprintf(FILE *restrict stream, const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vfprintf(stream, format, ap);
  va_end(ap);
  return ret;
}
