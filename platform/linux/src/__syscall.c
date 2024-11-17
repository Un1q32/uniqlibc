#include <errno.h>

long __syscallret2 = 0;

long __syscall_end(long ret, long ret2) {
  if (ret >= 0 || ret < -4095) {
    __syscallret2 = ret2;
    return ret;
  } else {
    errno = -ret;
    return -1;
  }
}
