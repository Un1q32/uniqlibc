#ifndef _SYS_IOCTL_H_
#define _SYS_IOCTL_H_

#include <sys/cdefs.h>

#if defined(__linux__)
#include <sys/linux/ttycom.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/ttycom.h>
#elif defined(__APPLE__)
#include <sys/darwin/ttycom.h>
#else
#error platform not supported
#endif

__BEGIN_DECLS
extern int ioctl(int, unsigned long, ...);
__END_DECLS

#endif
