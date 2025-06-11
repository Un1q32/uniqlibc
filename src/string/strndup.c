#include <stdlib.h>
#include <string.h>

char *strndup(const char *str, size_t maxlen) {
  size_t len = strnlen(str, maxlen);
  char *ret = malloc(len + 1);
  if (!ret)
    return NULL;
  memcpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}
