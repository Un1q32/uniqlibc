#include <stdio.h>
#include <sys/time.h>

int main(void) {
  struct timeval tv;
  fputs("UNIX Epoch: ", stdout);
  while (1) {
    gettimeofday(&tv, NULL);
    printf("\033[13G%ld.%06d", tv.tv_sec, tv.tv_usec);
    fflush(stdout);
  }
  return 0;
}
