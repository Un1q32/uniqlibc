#include <string.h>

void *memmem(const void *haystack, size_t haystacklen, const void *needle,
             size_t needlelen) {
  if (needlelen > haystacklen)
    return NULL;

  const char *h = haystack;
  const char *n = needle;
  for (size_t i = 0; i <= haystacklen - needlelen; i++)
    if (memcmp(h + i, n, needlelen) == 0)
      return (void *)(h + i);
  return NULL;
}
