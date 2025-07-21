#ifndef _UNIQLIBC_LINUX_BRK_
#define _UNIQLIBC_LINUX_BRK_

#include <sys/syscall.h>
#include <unistd.h>

static inline void *linux_brk(void *addr) {
  return (void *)syscall(SYS_brk, addr);
}

#endif
