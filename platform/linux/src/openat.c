#include <fcntl.h>
#include <stdarg.h>
#include <sys/syscall.h>
#include <unistd.h>

int openat(int fd, const char *path, int flags, ...) {
  mode_t mode = 0;
  if (flags & O_CREAT) {
    va_list va_args;
    va_start(va_args, flags);
    mode = va_arg(va_args, int);
    va_end(va_args);
  }
  return syscall(SYS_openat, fd, path, flags, mode);
}
