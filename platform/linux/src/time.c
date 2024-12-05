#include <stdlib.h>
#include <sys/time.h>

time_t time(time_t *tloc) {
#ifdef SYS_time
  return syscall(SYS_time, tloc);
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  if (tloc != NULL)
    *tloc = tv.tv_sec;
  return tv.tv_sec;
#endif
}
