#include <sys/signal.h>
#include <sys/syscall.h>
#include <unistd.h>

pid_t fork(void) {
#ifdef SYS_fork
  return syscall(SYS_fork);
#else
  return syscall(SYS_clone, SIGCHLD, 0);
#endif
}
