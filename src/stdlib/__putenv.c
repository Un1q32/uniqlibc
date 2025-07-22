#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int __putenv(char *env, ssize_t i, bool shouldfree) {
  /*
   * i is an index into environ to an entry we should
   * replace. an index of -1 means we reallocate environ and
   * prepend the entry instead of replacing another entry.
   */
  if (i != -1) {
    if (__envshouldfree) {
      if (__envshouldfree[i])
        free(environ[i]);
    } else {
      size_t j = 0;
      while (environ[j])
        ++j;
      char *new_envshouldfree = aligned_alloc(1, j);
      /*
       * if this fails, there is a memory leak, since an
       * unallocated __envshouldfree list is treated as all false.
       */
      if (new_envshouldfree) {
        __envshouldfree = new_envshouldfree;
        bzero(__envshouldfree, j);
        __envshouldfree[i] = shouldfree ? 1 : 0;
      }
    }
    environ[i] = env;
  } else {
    size_t j = 0;
    while (environ[j])
      ++j;

    char **new_environ = aligned_alloc(sizeof(char *), (j + 2) * sizeof(char *));
    if (!new_environ)
      return -1;
    char *new_envshouldfree = aligned_alloc(1, j + 1);
    if (!new_envshouldfree) {
      free(new_environ);
      return -1;
    }
    memcpy(new_environ + 1, environ, (j + 1) * sizeof(char *));
    if (__envshouldfree) {
      memcpy(new_envshouldfree + 1, __envshouldfree, j);
      free(__envshouldfree);
    } else
      bzero(new_envshouldfree, j + 1);
    new_environ[0] = env;
    new_envshouldfree[0] = shouldfree ? 1 : 0;

    if (__environ_shouldfree)
      free(environ);
    environ = new_environ;
    __environ_shouldfree = true;
    __envshouldfree = new_envshouldfree;
  }
  return 0;
}
