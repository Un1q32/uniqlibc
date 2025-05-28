#include <unistd.h>

int execvp(const char *filename, char *const argv[]) {
  return execvpe(filename, argv, environ);
}
