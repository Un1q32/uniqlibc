#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  if (!(stream->flags & __SRD) && !(stream->flags & __SRW)) {
    stream->flags |= __SERR;
    return 0;
  }
  fflush(stream);
  if (stream->read) {
    ssize_t readret = stream->read(stream->fd, ptr, size * nmemb);
    if (readret < 0) {
      stream->flags |= __SERR;
      return 0;
    } else if (readret == 0) {
      stream->flags |= __SEOF;
      return 0;
    }
    return readret / size;
  } else {
    stream->flags |= __SERR;
    return 0;
  }
}
