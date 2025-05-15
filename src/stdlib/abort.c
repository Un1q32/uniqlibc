#include <unistd.h>

void abort(void) {
  /* try to crash */
  *(volatile char *)0 = 0;
  _exit(127);
}
