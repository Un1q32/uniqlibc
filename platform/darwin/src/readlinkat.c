#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

ssize_t readlinkat(int fd, const char *path, char *buf, size_t bufsize) {
  if (fd == AT_FDCWD || path[0] == '/')
    return readlink(path, buf, bufsize);

  char fdpath[PATH_MAX + strlen(path) + 2];
  if (fcntl(fd, F_GETPATH, fdpath) == -1)
    return -1;

  if (path[0] != '\0') {
    strcat(fdpath, "/");
    strcat(fdpath, path);
  }
  return readlink(fdpath, buf, bufsize);
}
