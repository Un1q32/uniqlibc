#include <sys/syscall.h>
#include <unistd.h>

ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize) {
  return syscall(SYS_readlinkat, fd, path, buf, bufsize);
}
