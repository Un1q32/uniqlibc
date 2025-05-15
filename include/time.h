#ifndef _TIME_H_
#define _TIME_H_

#include <sys/cdefs.h>

typedef long time_t;

__BEGIN_DECLS
extern time_t time(time_t *);
__END_DECLS

#endif
