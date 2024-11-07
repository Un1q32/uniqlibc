#include <stdio.h>

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
  size_t total_size = size * nmemb;
  size_t readcount = 0;
  char *cptr = ptr;
  while (stream->ubufcount > 1 && total_size > 0) {
    *cptr++ = stream->ubuf[stream->ubufcount-- - 2];
    --total_size;
    ++readcount;
  }
  if (stream->ubufcount == 1 && total_size > 0) {
    *cptr++ = stream->uchar;
    stream->ubufcount = 0;
    --total_size;
    ++readcount;
  }
  ssize_t readret = 0;
  if (total_size > 0)
    readret = stream->read(stream->fd, cptr, total_size);
  if (readret < 0) {
    stream->flags |= __SERR;
    return 0;
  } else if (readret == 0 && total_size > 0) {
    stream->flags |= __SEOF;
    return 0;
  }
  return (readcount + readret) / size;
}
