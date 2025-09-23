#ifndef _SYS_TTYCOM_H_
#define _SYS_TTYCOM_H_

#if defined(__APPLE__)
#include <sys/darwin/ttycom.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/ttycom.h>
#endif

#endif
