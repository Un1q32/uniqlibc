#include <stdio.h>

int vfprintf(FILE *restrict stream, const char *restrict format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  char buf[vsnprintf(NULL, 0, format, ap2) + 1];
  va_end(ap2);
  int ret = vsnprintf(buf, sizeof(buf), format, ap);
  size_t fwriteret = fwrite(buf, 1, ret, stream);
  if (fwriteret != ret)
    return -1;
  return ret;
}
