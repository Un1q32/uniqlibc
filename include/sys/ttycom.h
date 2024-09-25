#ifndef _SYS_TTYCOM_H_
#define _SYS_TTYCOM_H_

#if defined(__FreeBSD__)
#include <sys/freebsd/ttycom.h>
#elif defined(__APPLE__)
#include <sys/darwin/ttycom.h>
#endif

#endif
