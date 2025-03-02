#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

int mkdirat(int fd, const char *path, mode_t mode) {
  if (fd == AT_FDCWD || path[0] == '/')
    return mkdir(path, mode);

  char fdpath[PATH_MAX + strlen(path) + 2];
  if (fcntl(fd, F_GETPATH, fdpath) == -1)
    return -1;

  strcat(fdpath, "/");
  strcat(fdpath, path);
  return mkdir(fdpath, mode);
}
