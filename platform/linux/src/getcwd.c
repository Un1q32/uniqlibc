#include <sys/syscall.h>
#include <unistd.h>

char *getcwd(char *buf, size_t size) {
  return (char *)syscall(SYS_getcwd, buf, size);
}
