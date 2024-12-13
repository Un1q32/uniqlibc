#ifndef _SYS_LINUX_SIGNAL_H_
#define _SYS_LINUX_SIGNAL_H_

#include <sys/types.h>

#define SIGABRT 6
#define SIGKILL 9

#ifdef __mips__
#define SIGUSR1 16
#define SIGCHLD 18
#else
#define SIGUSR1 10
#define SIGCHLD 17
#endif

typedef void (*sig_t)(int);

#endif
