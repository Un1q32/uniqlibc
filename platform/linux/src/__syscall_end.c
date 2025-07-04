#include <errno.h>
#include <unistd.h>

#if defined(__powerpc__) || defined(__POWERPC__)

long __syscall_error(long error) {
  errno = error;
  return -1;
}

#else

long __syscall_end(long ret, long ret2) {
  if (ret >= 0 || ret < -4095) {
    __syscallret2 = ret2;
    return ret;
  } else {
    errno = -ret;
    return -1;
  }
}

#endif
