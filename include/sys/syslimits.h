#ifndef _SYS_SYSLIMITS_H_
#define _SYS_SYSLIMITS_H_

#if defined(__linux__)
#include <sys/linux/syslimits.h>
#elif defined(__APPLE__)
#include <sys/darwin/syslimits.h>
#else
#error platform not supported
#endif

#endif
