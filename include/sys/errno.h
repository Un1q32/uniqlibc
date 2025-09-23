#ifndef _SYS_ERRNO_H_
#define _SYS_ERRNO_H_

#if defined(__linux__)
#include <sys/linux/errno.h>
#elif defined(__APPLE__)
#include <sys/darwin/errno.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/errno.h>
#else
#error platform not supported
#endif

#endif
