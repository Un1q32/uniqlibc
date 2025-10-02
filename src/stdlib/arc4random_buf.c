#include <stdio.h>
#include <stdlib.h>

void arc4random_buf(void *buf, size_t n) {
  static FILE *random = NULL;
  if (!random)
    random = fopen("/dev/urandom", "r");
  if (!random || fread(buf, 1, n, random) != n)
    abort();
}
