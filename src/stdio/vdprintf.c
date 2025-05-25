#include <stdio.h>
#include <unistd.h>

int vdprintf(int fd, const char *restrict format, va_list ap) {
  va_list ap2;
  va_copy(ap2, ap);
  char buf[vsnprintf(NULL, 0, format, ap2) + 1];
  va_end(ap2);
  int ret = vsnprintf(buf, sizeof(buf), format, ap);
  if (write(fd, buf, ret) != (ssize_t)ret)
    return -1;
  return ret;
}
