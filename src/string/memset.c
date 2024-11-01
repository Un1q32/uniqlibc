#include <stddef.h>

void *memset(void *buf, int c, size_t n) {
  unsigned char *p = buf;
  while (n--)
    *p++ = (unsigned char)c;
  return buf;
}
