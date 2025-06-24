#include <sys/syscall.h>
#include <unistd.h>

void *linux_brk(void *addr) { return (void *)syscall(SYS_brk, addr); }
