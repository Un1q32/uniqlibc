#include <stddef.h>

size_t strlcpy(char *restrict dst, const char *restrict src, size_t n) {
  const char *osrc = src;
  size_t nleft = n;
  if (nleft != 0)
    while (--nleft != 0 && (*dst++ = *src++) != '\0')
      ;
  if (nleft == 0) {
    if (n != 0)
      *dst = '\0';
    while (*src++)
      ;
  }
  return src - osrc - 1;
}
