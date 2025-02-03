#include <stddef.h>

char *stpncpy(char *restrict s1, const char *restrict s2, size_t n) {
  char *s = s1;
  const char *p = s2;

  while (n) {
    if ((*s = *s2))
      s2++;
    ++s;
    --n;
  }
  return s1 + (s2 - p);
}
