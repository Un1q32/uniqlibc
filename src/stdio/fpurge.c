#include <stdio.h>

int fpurge(FILE *stream) {
  stream->writebufcount = 0;
  return 0;
}
