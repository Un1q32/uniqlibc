#include <stdarg.h>

extern long __syscall(long, long, long, long, long, long, long, long);

long syscall(long number, ...) {
  va_list ap;
  long args[7];
  unsigned char i = 0;
  va_start(ap, number);
  while (i <= 7)
    args[i++] = va_arg(ap, long);
  return __syscall(args[0], args[1], args[2], args[3], args[4], args[5],
                   args[6], number);
}
