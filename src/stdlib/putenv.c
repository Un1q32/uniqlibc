#include <stdlib.h>
#include <string.h>

int putenv(char *string) {
  char *equal = strchr(string, '=');
  if (!equal)
    return unsetenv(string);
  char buf[equal - string + 1];
  memcpy(buf, string, equal - string);
  buf[equal - string] = '\0';
  return __putenv(string, __findenv(buf), false);
}
