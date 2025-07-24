#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/cdefs.h>
#include <sys/signal.h>
#include <sys/types.h>

__BEGIN_DECLS
extern int kill(pid_t, int);
extern int raise(int);
__END_DECLS

#endif
