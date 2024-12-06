#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

int creat(const char *path, mode_t mode) {
#ifdef SYS_creat
  return syscall(SYS_creat, mode);
#else
  return open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
#endif
}
