#include <stdlib.h>
#include <string.h>

char *strdup(const char *str) {
  size_t len = strlen(str) + 1;
  char *ret = malloc(len);
  if (ret)
    memcpy(ret, str, len);
  return ret;
}
