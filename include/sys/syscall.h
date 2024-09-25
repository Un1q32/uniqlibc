#ifndef _SYS_SYSCALL_H_
#define _SYS_SYSCALL_H_

#if defined(__linux__)
#include <sys/linux/syscall.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/syscall.h>
#elif defined(__APPLE__)
#include <sys/darwin/syscall.h>
#else
#error platform not supported
#endif

#endif
