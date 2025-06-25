#ifndef _UNIQLIBC_LINUX_BRK_
#define _UNIQLIBC_LINUX_BRK_

#include <sys/syscall.h>
#include <unistd.h>

#define linux_brk(addr) (void *)syscall(SYS_brk, addr)

#endif
