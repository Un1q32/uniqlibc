#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int gettimeofday(struct timeval *tv, void *tz) {
  if (tv) {
    long ret = syscall(SYS_gettimeofday, tv, NULL);
    if (ret == -1)
      return -1;
    else if (ret != 0) {
      tv->tv_sec = ret;
      tv->tv_usec = __syscallret2;
    }
  }
  if (tz) {
    struct timezone *tmp_tz = (struct timezone *)tz;
    tmp_tz->tz_minuteswest = 0;
    tmp_tz->tz_dsttime = 0;
  }
  return 0;
}
