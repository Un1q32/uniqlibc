#include <limits.h>
#include <string.h>

char *dirname(char *path) {
  static char ret[PATH_MAX];
  if (!path || *path == '\0') {
    memcpy(ret, ".", 2);
    return ret;
  }

  size_t pathlen = strlen(path);
  if (pathlen >= PATH_MAX) {
    memcpy(ret, ".", 2);
    return ret;
  }

  memcpy(ret, path, pathlen + 1);
  while (1) {
    char *lastslash = strrchr(ret, '/');
    if (!lastslash) {
      memcpy(ret, ".", 2);
      return ret;
    } else if (lastslash[1] == '\0')
      lastslash[0] = '\0';
    else {
      lastslash[0] = '\0';
      return ret;
    }
  }
}
