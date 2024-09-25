#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int gettimeofday(struct timeval *tv, void *tz) {
  return syscall(SYS_gettimeofday, tv, tz);
}
