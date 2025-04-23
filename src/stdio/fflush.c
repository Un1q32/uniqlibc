#include <stdio.h>

int fflush(FILE *stream) {
  if (!stream) {
    if (__open_stream_list) {
      size_t i = *((size_t *)__open_stream_list);
      while (i) {
        if (__open_stream_list[i])
          fflush(__open_stream_list[i]);
        i--;
      }
    }
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
    return 0;
  }
  if (stream->flags & __SWR) {
    size_t bufcount = stream->bufcount;
    if (!bufcount)
      return 0;
    if (!stream->write) {
      stream->flags |= __SERR;
      return EOF;
    }
    ssize_t writeret = stream->write(stream->fd, stream->buf, bufcount);
    if (writeret != bufcount) {
      stream->flags |= __SERR;
      return EOF;
    } else
      stream->bufcount = 0;
  }
  return 0;
}
