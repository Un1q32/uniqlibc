#ifndef _SYS_TERMIOS_H_
#define _SYS_TERMIOS_H_

#if defined(__linux__)
#include <sys/linux/termios.h>
#elif defined(__APPLE__)
#include <sys/darwin/termios.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/termios.h>
#else
#error platform not supported
#endif

#endif
