#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

int dup2(int oldfd, int newfd) {
#ifdef SYS_dup2
  return syscall(SYS_dup2, oldfd, newfd);
#else
  if (oldfd != newfd)
    return syscall(SYS_dup3, oldfd, newfd, 0);
  else {
    if (fcntl(oldfd, F_GETFD) >= 0)
      return oldfd;
    return -1;
  }
#endif
}
