#include <errno.h>
#include <stdlib.h>
#include <string.h>

int putenv(char *string) {
  if (!string || !strchr(string, '=')) {
    errno = EINVAL;
    return -1;
  }
  return __putenv(string, -1, false);
}
