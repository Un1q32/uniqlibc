#ifndef _SYS_SIGNAL_H_
#define _SYS_SIGNAL_H_

#if defined(__linux__)
#include <sys/linux/signal.h>
#elif defined(__APPLE__)
#include <sys/darwin/signal.h>
#else
#error platform not supported
#endif

#endif
