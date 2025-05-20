#include <stdio.h>
#include <stdlib.h>

int ungetc(int c, FILE *stream) {
  if (stream->ungetcbufcount == 0) {
    stream->ungetcchar = c;
    stream->ungetcbufcount++;
  } else {
    void *new_ubuf = realloc(stream->ungetcbuf, stream->ungetcbufcount);
    if (!new_ubuf)
      return EOF;
    stream->ungetcbuf = new_ubuf;
    stream->ungetcbuf[stream->ungetcbufcount++ - 1] = c;
  }
  return c;
}
