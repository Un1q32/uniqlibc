#include <sys/resource.h>
#include <sys/syscall.h>
#include <unistd.h>

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage) {
  return syscall(SYS_wait4, pid, status, options, rusage);
}
