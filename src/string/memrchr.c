#include <stddef.h>

void *memrchr(const void *s, int c, size_t n) {
  const unsigned char *r = (unsigned char *)s + n;
  while (n--)
    if (*--r == ((unsigned char)c))
      return (void *)r;
  return NULL;
}
