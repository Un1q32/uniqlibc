#include <stdio.h>
#include <stdlib.h>

int setvbuf(FILE *restrict stream, char *restrict buf, int mode, size_t size) {
  if (mode != _IONBF && mode != _IOLBF && mode != _IOFBF)
    return -1;

  if (stream->flags & __SFREEBUF)
    free(stream->buf);
  stream->buf = buf;
  stream->bufsize = size;
  stream->flags &= ~__SFREEBUF;
  if (mode == _IONBF) {
    stream->flags |= __SNBF;
    stream->flags &= ~__SLBF;
  } else {
    stream->flags &= ~_IONBF;
    if (mode == _IOLBF)
      stream->flags |= __SLBF;
    else
      stream->flags &= ~__SLBF;
  }

  return 0;
}
