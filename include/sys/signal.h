#ifndef _SYS_SIGNAL_H_
#define _SYS_SIGNAL_H_

#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGKILL 9
#define SIGTERM 15

#if defined(__linux__)
#include <sys/linux/signal.h>
#elif defined(__APPLE__)
#include <sys/darwin/signal.h>
#else
#error platform not supported
#endif

#endif
