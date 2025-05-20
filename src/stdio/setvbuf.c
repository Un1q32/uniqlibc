#include <stdio.h>
#include <stdlib.h>

int setvbuf(FILE *restrict stream, char *restrict buf, int mode, size_t size) {
  if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
    return EOF;

  if (stream->flags & __STDIO_MALLOCED_WRITEBUF)
    free(stream->buf);
  stream->buf = buf;
  stream->bufsize = size;
  stream->flags &= ~__STDIO_MALLOCED_WRITEBUF;
  if (mode == _IONBF) {
    stream->flags |= __STDIO_UNBUFFERED;
    stream->flags &= ~__STDIO_LINEBUFFERED;
  } else {
    stream->flags &= ~_IONBF;
    if (mode == _IOLBF)
      stream->flags |= __STDIO_LINEBUFFERED;
    else
      stream->flags &= ~__STDIO_LINEBUFFERED;
  }

  return 0;
}
