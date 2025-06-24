#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

int access(const char *path, int mode) {
#ifdef SYS_access
  return syscall(SYS_access, path, mode);
#else
  return syscall(SYS_faccessat, AT_FDCWD, path, mode, 0);
#endif
}
