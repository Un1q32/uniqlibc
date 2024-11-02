#include <stdio.h>

int snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vsnprintf(str, size, format, ap);
  va_end(ap);
  return ret;
}
