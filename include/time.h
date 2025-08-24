#ifndef _TIME_H_
#define _TIME_H_

#include <sys/cdefs.h>

#if defined(__linux__) && defined(__x86_64__)
typedef long long time_t;
#else
typedef long time_t;
#endif

__BEGIN_DECLS
extern time_t time(time_t *);
__END_DECLS

#endif
