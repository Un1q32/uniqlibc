#include <unistd.h>

int execv(const char *filename, char *const argv[]) {
  return execve(filename, argv, environ);
}
