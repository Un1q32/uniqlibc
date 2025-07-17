#include <errno.h>

long __syscallret2 = 0;

long __syscall_error(long err) {
  errno = err;
  return -1;
}

long __syscall_success(long ret, long ret2) {
  __syscallret2 = ret2;
  return ret;
}
