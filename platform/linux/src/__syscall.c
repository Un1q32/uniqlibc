#include <errno.h>
#include <stdarg.h>

extern long __syscall(long, long, long, long, long, long, long, long);

long __syscallret2 = 0;

long syscall(long number, ...) {
  va_list ap;
  long args[7];
  unsigned char i = 0;
  va_start(ap, number);
  while (i <= 7)
    args[i++] = va_arg(ap, long);
  return __syscall(args[0], args[1], args[2], args[3], args[4], args[5], args[6], number);
}

long __syscall_end(long ret, long ret2) {
  if (ret >= 0 || ret < -4095) {
    __syscallret2 = ret2;
    return ret;
  } else {
    errno = -ret;
    return -1;
  }
}
