#include <stdio.h>

int dprintf(int fd, const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vdprintf(fd, format, ap);
  va_end(ap);
  return ret;
}
