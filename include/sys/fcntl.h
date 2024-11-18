#ifndef _SYS_FCNTL_H_
#define _SYS_FCNTL_H_

#if defined(__linux__)
#include <sys/linux/fcntl.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/fcntl.h>
#elif defined(__APPLE__)
#include <sys/darwin/fcntl.h>
#else
#error platform not supported
#endif

#endif
