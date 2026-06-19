#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define LOOPS 100000

size_t get_anon_rss_bytes(void) {
#ifdef __linux__
  int fd = open("/proc/self/smaps_rollup", O_RDONLY);
  if (fd < 0)
    return 0;

  char buf[512];
  int n = read(fd, buf, sizeof(buf) - 1);
  close(fd);
  if (n <= 0)
    return 0;
  buf[n] = '\0';

  char *p = buf;
  while (*p) {
    if (strncmp(p, "Anonymous:", 10) == 0) {
      p += 10;
      while (*p == ' ' || *p == '\t')
        p++;
      size_t kb = 0;
      while (*p >= '0' && *p <= '9')
        kb = kb * 10 + (size_t)(*p++ - '0');
      return kb * 1024;
    }
    while (*p && *p != '\n')
      p++;
    if (*p)
      p++;
  }
#endif
  return 0;
}

int main(void) {
  size_t i = 0;
  void *ptrs[LOOPS];
  struct timeval tv, tv2;
  gettimeofday(&tv, NULL);
  do {
    ptrs[i] = malloc(rand() % 200);
  } while (++i < LOOPS);
  printf("%zu bytes used\n", get_anon_rss_bytes());
  while (i)
    free(ptrs[--i]);
  gettimeofday(&tv2, NULL);
  long long time = tv2.tv_usec - tv.tv_usec;
  time += (tv2.tv_sec - tv.tv_sec) * 1000000;
  printf("%d malloc/free calls took %lld usec\n", LOOPS, time);
  return 0;
}
