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
  if (!(stream->flags & __SWR))
    return 0;
  if (stream->write && stream->bufcount > 0) {
    ssize_t writeret = stream->write(stream->fd, stream->buf, stream->bufcount);
    if (writeret == -1)
      return EOF;
    else
      stream->bufcount = 0;
  }
  return 0;
}
