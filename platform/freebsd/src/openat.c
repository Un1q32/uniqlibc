#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
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

  if (fd == AT_FDCWD || path[0] == '/')
    return open(path, flags, mode);

  char fdpath[PATH_MAX + strlen(path) + 2];
  if (fcntl(fd, F_GETPATH, fdpath) == -1)
    return -1;

  strcat(fdpath, "/");
  strcat(fdpath, path);
  return open(fdpath, flags, mode);
}
