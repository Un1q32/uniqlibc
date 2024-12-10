#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#if defined(__linux__)
#include <sys/linux/stat.h>
#elif defined(__FreeBSD__)
#include <sys/freebsd/stat.h>
#elif defined(__APPLE__)
#include <sys/darwin/stat.h>
#else
#error platform not supported
#endif

#include <sys/cdefs.h>

__BEGIN_DECLS
extern int mkdir(const char *, mode_t);
extern int mkdirat(int, const char *, mode_t);
extern int fstat(int, struct stat *);
extern int stat(const char *, struct stat *);
extern int stat64(const char *, struct stat64 *);
extern int lstat(const char *, struct stat *);
extern mode_t umask(mode_t);
extern int chmod(const char *, mode_t);
extern int fchmod(int, mode_t);
__END_DECLS

#endif
