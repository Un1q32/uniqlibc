#include <sys/syscall.h>
#include <unistd.h>
#ifndef SYS_fork
#include <signal.h>
#endif

pid_t fork(void) {
#ifdef SYS_fork
  return syscall(SYS_fork);
#else
  return syscall(SYS_clone, SIGCHLD, 0);
#endif
}
