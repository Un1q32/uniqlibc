#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int __putenv(char *env, ssize_t i, bool shouldfree) {
  if (i != -1) {
    if (__envshouldfree && __envshouldfree[i])
      free(environ[i]);

    __envshouldfree[i] = shouldfree;
    environ[i] = env;
  } else {
    i = 0;
    while (environ[i])
      ++i;

    char **new_environ = malloc((i + 2) * sizeof(char *));
    memcpy(new_environ + 1, environ, (i + 1) * sizeof(char *));
    if (!new_environ)
      return -1;
    bool *new_envshouldfree = malloc(i + 1);
    if (!new_envshouldfree) {
      free(new_environ);
      return -1;
    }
    if (__envshouldfree) {
      free(environ);
      memcpy(new_envshouldfree + 1, __envshouldfree, i);
    } else
      bzero(new_envshouldfree, i + 1);
    new_environ[0] = env;
    new_envshouldfree[0] = shouldfree;

    environ = new_environ;
    __envshouldfree = new_envshouldfree;
  }
  return 0;
}
