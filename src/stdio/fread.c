#include <stdio.h>
#include <string.h>

size_t fread(void *restrict ptr, size_t size, size_t nmemb,
             FILE *restrict stream) {
  if (!(stream->flags & __SRD)) {
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
      if ((size_t)readret > total_size) {
        memcpy(cptr, buf, total_size);
        memcpy(stream->rbuf, buf + total_size, readret - total_size);
        stream->rbufcount = readret - total_size;
        break;
      } else {
        memcpy(cptr, buf, readret);
        total_size -= readret;
        if (readret < BUFSIZ) {
          stream->flags |= __SEOF;
          break;
        } else
          cptr += readret;
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
