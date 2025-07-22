#include <stdlib.h>
#include <unistd.h>

int clearenv(void) {
  if (__envshouldfree) {
    size_t i = 0;
    while (environ[i])
      if (__envshouldfree[i])
        free(environ[i]);
  }
  if (__environ_shouldfree) {
    char **new_environ = aligned_alloc(sizeof(char *), sizeof(char *));
    if (new_environ) {
      free(environ);
      environ = new_environ;
    }
  }
  environ[0] = NULL;
  return 0;
}
