#include <stdlib.h>
#include <string.h>

int putenv(char *string) {
  if (!strchr(string, '='))
    return unsetenv(string);
  return __putenv(string, -1, false);
}
