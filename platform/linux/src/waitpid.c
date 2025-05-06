#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t waitpid(pid_t pid, int *status, int options) {
#ifdef SYS_waitpid
  return syscall(SYS_waitpid, pid, status, options);
#else
  return wait4(pid, status, options, NULL);
#endif
}
