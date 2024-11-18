#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>

int sigaction(int signum, const struct sigaction *restrict act,
              struct sigaction *restrict oldact) {
  return syscall(SYS_rt_sigaction, signum, act, oldact, sizeof(sigset_t));
}
