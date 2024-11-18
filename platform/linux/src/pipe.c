#include <sys/syscall.h>
#include <unistd.h>

int pipe(int pipefd[2]) {
#ifdef SYS_pipe
  return syscall(SYS_pipe, pipefd);
#else
  return syscall(SYS_pipe2, pipefd, 0);
#endif
}
