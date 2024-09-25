#include <stdio.h>

void setbuffer(FILE *stream, char *buf, size_t size) {
  if (size == 0)
    setvbuf(stream, buf, _IONBF, 0);
  else
    setvbuf(stream, buf, _IOFBF, size);
}
