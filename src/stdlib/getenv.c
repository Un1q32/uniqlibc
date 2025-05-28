#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getenv(const char *name) {
  ssize_t i = __findenv(name);
  if (i == -1)
    return NULL;
  return strchr(environ[i], '=') + 1;
}
