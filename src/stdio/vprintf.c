#include <stdio.h>

int vprintf(const char *format, va_list ap) {
  if (stdout)
    return vfprintf(stdout, format, ap);
  return EOF;
}
