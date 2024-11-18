#ifndef _SYS_LINUX_SIGNAL_H_
#define _SYS_LINUX_SIGNAL_H_

#include <sys/types.h>

#ifdef __mips__
#define SIGCHLD 18
#else
#define SIGCHLD 17
#endif

typedef void (*sig_t)(int);

#endif
