#include <signal.h>
#include <unistd.h>

int raise(int signum) { return kill(getpid(), signum); }
