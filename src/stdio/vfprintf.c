#include <stdio.h>
#include <stdlib.h>

int vfprintf(FILE *restrict stream, const char *restrict format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  int bufsize = vsnprintf(NULL, 0, format, ap2);
  va_end(ap2);
  if (bufsize == -1)
    return -1;
  char *buf = malloc(bufsize + 1);
  if (!buf)
    return -1;
  int ret = vsnprintf(buf, sizeof(buf), format, ap);
  if (fwrite(buf, 1, ret, stream) != (size_t)ret)
    return -1;
  free(buf);
  return ret;
}
