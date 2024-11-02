#include <stdio.h>

int vprintf(const char *restrict format, va_list ap) {
  if (stdout)
    return vfprintf(stdout, format, ap);
  return EOF;
}
