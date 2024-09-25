#include <sys/syscall.h>
#include <unistd.h>

pid_t fork(void) { return syscall(SYS_fork); }
