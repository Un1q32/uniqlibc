#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define LOOPS 32767

int main(void) {
  size_t i = 0;
  void *ptrs[LOOPS];
  struct timeval tv, tv2;
  gettimeofday(&tv, NULL);
  do {
    ptrs[i] = malloc(rand() % 200);
  } while(++i < LOOPS);
  while (i)
    free(ptrs[--i]);
  gettimeofday(&tv2, NULL);
  long long time = tv2.tv_usec - tv.tv_usec;
  time += (tv2.tv_sec - tv.tv_sec) * 1000000;
  printf("%d malloc/free calls took %lld usec\n", LOOPS, time);
  return 0;
}
