#include <stdbool.h>
#include <stdlib.h>

extern char **environ;

int unsetenv(const char *name) {
  int i = __findenv(name);
  if (i == -1)
    return 0;
  if (__envshouldfree && __envshouldfree[i])
    free(environ[i]);
  while (environ[i + 1] != NULL) {
    environ[i] = environ[i + 1];
    if (__envshouldfree)
      __envshouldfree[i] = __envshouldfree[i + 1];
    i++;
  }
  environ[i] = NULL;
  return 0;
}
