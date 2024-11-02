#include <stdio.h>

size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb,
              FILE *restrict stream) {
  if (!(stream->flags & __SWR) && !(stream->flags & __SRW)) {
    stream->flags |= __SERR;
    return 0;
  }
  if (stream->flags & __SNBF) {
    if (stream->write) {
      ssize_t writeret = stream->write(stream->fd, ptr, size * nmemb);
      if (writeret < 0) {
        stream->flags |= __SERR;
        return 0;
      }
      return writeret / size;
    } else {
      stream->flags |= __SERR;
      return 0;
    }
  } else {
    if (!stream->buf) {
      stream->flags |= __SERR;
      return 0;
    }
    const char *src = ptr;
    size_t s = size * nmemb;
    char *data = stream->buf + stream->bufcount;
    if (stream->flags & __SLBF) {
      while (s--) {
        if (stream->bufcount == stream->bufsize - 2) {
          fflush(stream);
          data = stream->buf;
        }
        *data++ = *src++;
        stream->bufcount++;
        if (*(src - 1) == '\n') {
          fflush(stream);
          data = stream->buf;
        }
      }
    } else {
      while (s--) {
        if (stream->bufcount == stream->bufsize) {
          fflush(stream);
          data = stream->buf;
        }
        *data++ = *src++;
        stream->bufcount++;
      }
    }
    return nmemb;
  }
}
