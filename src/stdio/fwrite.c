#include <stdio.h>
#include <string.h>

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
    char *dst = stream->buf + stream->bufcount;
    size_t bufsize = stream->bufsize;
    if (stream->flags & __SLBF) {
      while (s) {
        if (stream->bufcount == bufsize) {
          fflush(stream);
          dst = stream->buf;
        }
        size_t towrite = bufsize - stream->bufcount;
        if (s < towrite)
          towrite = s;
        char *newl = memchr(src, '\n', towrite);
        if (newl)
          towrite = newl - src + 1;
        memcpy(dst, src, towrite);
        stream->bufcount += towrite;
        src += towrite;
        s -= towrite;
        if (newl) {
          fflush(stream);
          dst = stream->buf;
        }
      }
    } else {
      while (s) {
        if (stream->bufcount == bufsize) {
          fflush(stream);
          dst = stream->buf;
        }
        size_t towrite = bufsize - stream->bufcount;
        if (s < towrite)
          towrite = s;
        memcpy(dst, src, towrite);
        stream->bufcount += towrite;
        src += towrite;
        s -= towrite;
      }
    }
    return nmemb;
  }
}
