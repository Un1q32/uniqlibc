#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#if defined(__linux__)
#include <sys/linux/mman.h>
#elif defined(__APPLE__)
#include <sys/darwin/mman.h>
#else
#error platform not supported
#endif

#endif
