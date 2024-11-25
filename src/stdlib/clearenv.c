#include <stdbool.h>
#include <stdlib.h>

extern char **environ;

int clearenv(void) {
  if (__envshouldfree) {
    size_t i = 0;
    while (environ[i])
      if (__envshouldfree[i])
        free(environ[i]);
    free(environ);
  }
  environ = malloc(sizeof(char *));
  if (environ == NULL)
    return -1;
  environ[0] = NULL;
  return 0;
}
