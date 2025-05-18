#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

time_t time(time_t *tloc) {
#ifdef SYS_time
  return syscall(SYS_time, tloc);
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  if (tloc)
    *tloc = tv.tv_sec;
  return tv.tv_sec;
#endif
}
