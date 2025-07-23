#include <signal.h>
#include <unistd.h>

#if defined(__linux__) || defined(__APPLE__)
#define SIGABRT 6
#else
#error platform not supported
#endif

void abort(void) {
  /* try to crash */
  raise(SIGABRT);
  *(volatile char *)0 = 0;
  _exit(127);
}
