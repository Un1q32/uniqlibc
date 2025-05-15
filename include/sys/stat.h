#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#if defined(__linux__)
#include <sys/linux/stat.h>
#elif defined(__APPLE__)
#include <sys/darwin/stat.h>
#else
#error platform not supported
#endif

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS
extern int mkdir(const char *, mode_t);
extern int mkdirat(int, const char *, mode_t);
extern mode_t umask(mode_t);
extern int chmod(const char *, mode_t);
extern int fchmod(int, mode_t);
__END_DECLS

#endif
