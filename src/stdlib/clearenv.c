#include <stdlib.h>
#include <unistd.h>

int clearenv(void) {
  if (__envshouldfree) {
    size_t i = 0;
    while (environ[i])
      if (__envshouldfree[i])
        free(environ[i]);
    free(environ);
  }
  environ = malloc(sizeof(char *));
  if (!environ)
    return -1;
  environ[0] = NULL;
  return 0;
}
