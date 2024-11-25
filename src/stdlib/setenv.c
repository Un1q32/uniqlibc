#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int setenv(const char *name, const char *value, int overwrite) {
  if (!name || name[0] == '\0' || strchr(name, '=')) {
    errno = EINVAL;
    return -1;
  }
  ssize_t i = __findenv(name);
  if (i != -1 && !overwrite)
    return 0;
  size_t namelen = strlen(name);
  size_t valuelen = strlen(value);
  size_t strsize = namelen + valuelen + 2;
  char *env_str = malloc(strsize);
  if (!env_str)
    return -1;
  memcpy(env_str, name, namelen);
  env_str[namelen] = '=';
  memcpy(env_str + namelen + 1, value, valuelen);
  env_str[strsize] = '\0';
  return __putenv(env_str, i, true);
}
