#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <sys/cdefs.h>
#include <sys/fcntl.h>
#include <sys/types.h>

__BEGIN_DECLS
extern int creat(const char *, mode_t);
extern int open(const char *, int, ...);
extern int openat(int, const char *, int, ...);
extern int fcntl(int, int, ...);
__END_DECLS

#endif
