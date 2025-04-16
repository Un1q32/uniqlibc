#include <stdio.h>
#include <string.h>

size_t fread(void *restrict ptr, size_t size, size_t nmemb,
             FILE *restrict stream) {
  if (!(stream->flags & __SRD) && !(stream->flags & __SRW)) {
    stream->flags |= __SERR;
    return 0;
  }
  fflush(stream);
  if (!stream->read) {
    stream->flags |= __SERR;
    return 0;
  }
  size_t total_size = size * nmemb, ts = total_size;
  char *cptr = ptr;
  while (stream->ubufcount > 1 && total_size > 0) {
    *cptr++ = stream->ubuf[--(stream->ubufcount) - 1];
    --total_size;
  }
  if (stream->ubufcount == 1 && total_size > 0) {
    *cptr++ = stream->uchar;
    stream->ubufcount = 0;
    --total_size;
  }
  while (stream->rbufcount > 1 && total_size > 0) {
    *cptr++ = stream->rbuf[--(stream->rbufcount)];
    --total_size;
  }
  ssize_t readret = 0;
  char buf[BUFSIZ];
  while (total_size > 0) {
    readret = stream->read(stream->fd, buf, BUFSIZ);
    if (readret > 0) {
      size_t i = 0;
      while (total_size > 0 && readret > 0) {
        *cptr++ = buf[i++];
        --readret;
        --total_size;
      }
      if (readret > 0) {
        memcpy(stream->rbuf, buf + i, readret);
        stream->rbufcount = readret;
      }
    } else if (readret == 0) {
      stream->flags |= __SEOF;
      break;
    } else {
      stream->flags |= __SERR;
      break;
    }
  }
  return ts - total_size;
}
