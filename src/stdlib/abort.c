#include <signal.h>
#include <unistd.h>

void abort(void) {
  /* try to crash */
  raise(SIGABRT);
  *(volatile char *)0 = 0;
  _exit(127);
  while (1)
    ;
}
