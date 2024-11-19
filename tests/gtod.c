#include <stdio.h>
#include <sys/time.h>

int main(void) {
  struct timeval tv;
  while (1) {
    gettimeofday(&tv, NULL);
    printf("Unix Epoch: %ld.%06d\r", tv.tv_sec, tv.tv_usec);
    fflush(stdout);
  }
  return 0;
}
