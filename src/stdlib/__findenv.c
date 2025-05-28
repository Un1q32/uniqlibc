#include <string.h>
#include <unistd.h>

ssize_t __findenv(const char *name) {
  for (ssize_t i = 0; environ[i]; i++) {
    const char *p = strchr(environ[i], '=');
    if (!strncmp(name, environ[i], p - environ[i]))
      return i;
  }
  return -1;
}
