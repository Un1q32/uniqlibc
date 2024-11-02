#include <stdio.h>

int sprintf(char *restrict str, const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vsprintf(str, format, ap);
  va_end(ap);
  return ret;
}
