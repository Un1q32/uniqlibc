#include <stdio.h>
#include <stdlib.h>

int ungetc(int c, FILE *stream) {
  if (stream->ubufcount == 0) {
    stream->uchar = c;
    stream->ubufcount++;
  } else {
    void *new_ubuf = realloc(stream->ubuf, stream->ubufcount);
    if (!new_ubuf)
      return EOF;
    stream->ubuf = new_ubuf;
    stream->ubuf[stream->ubufcount++ - 1] = c;
  }
  return c;
}
