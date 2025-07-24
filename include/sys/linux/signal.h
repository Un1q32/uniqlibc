#ifndef _SYS_LINUX_SIGNAL_H_
#define _SYS_LINUX_SIGNAL_H_

#define SIGABRT 6
#ifdef __mips__
#define SIGCHLD 18
#else
#define SIGCHLD 17
#endif

#endif
