#include <sys/syscall.h>
#include <unistd.h>

pid_t vfork(void) {
#ifdef SYS_vfork
  return syscall(SYS_vfork);
#else
  return fork();
#endif
}
