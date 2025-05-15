#include <sys/syscall.h>
#include <unistd.h>

#ifdef __mips__
#define SIGCHLD 18
#else
#define SIGCHLD 17
#endif

pid_t fork(void) {
#ifdef SYS_fork
  return syscall(SYS_fork);
#else
  return syscall(SYS_clone, SIGCHLD, 0);
#endif
}
