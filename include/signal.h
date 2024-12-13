#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <sys/cdefs.h>
#include <sys/signal.h>

typedef int sig_atomic_t;

__BEGIN_DECLS
extern int kill(pid_t, int);
extern int raise(int);
#ifndef __linux__ /* TODO: fix signals on linux */
extern sig_t signal(int, sig_t);
extern int sigaction(int, const struct sigaction *, struct sigaction *);
extern int sigemptyset(sigset_t *);
extern int sigismember(const sigset_t *, int);
#endif
__END_DECLS

#endif
