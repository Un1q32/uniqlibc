#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>

int nanosleep(const struct timespec *req, struct timespec *rem) {
  return syscall(SYS_nanosleep, req, rem);
}
