#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

int mkdir(const char *path, mode_t mode) {
#ifdef SYS_mkdir
  return syscall(SYS_mkdir, path, mode);
#else
  return syscall(SYS_mkdirat, AT_FDCWD, path, mode);
#endif
}
