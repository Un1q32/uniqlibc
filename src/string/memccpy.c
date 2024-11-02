#include <stddef.h>

void *memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
  if (n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    unsigned char uc = c;
    do {
      if ((*d++ = *s++) == uc)
        return (d);
    } while (--n != 0);
  }
  return 0;
}
