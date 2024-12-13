#include <signal.h>
#include <unistd.h>

void abort(void) {
  raise(SIGABRT);
  usleep(10000);
  // try to crash
  *(volatile char *)0 = 0;
  raise(SIGKILL);
  _exit(127);
}
