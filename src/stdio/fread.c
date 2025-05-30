#include <stdio.h>
#include <string.h>

size_t fread(void *restrict ptr, size_t size, size_t nmemb,
             FILE *restrict stream) {
  if (!stream->read) {
    stream->flags |= __STDIO_ERROR;
    return 0;
  }
  fflush(stream);
  size_t total_size = size * nmemb, ts = total_size;
  char *cptr = ptr;
  while (stream->ungetcbufcount > 1 && total_size > 0) {
    *cptr++ = stream->ungetcbuf[--(stream->ungetcbufcount) - 1];
    --total_size;
  }
  if (stream->ungetcbufcount == 1 && total_size > 0) {
    *cptr++ = stream->ungetcchar;
    stream->ungetcbufcount = 0;
    --total_size;
  }
  while (stream->readbufcount > 1 && total_size > 0) {
    *cptr++ = stream->readbuf[--(stream->readbufcount)];
    --total_size;
  }
  ssize_t readret = 0;
  char buf[BUFSIZ];
  while (total_size > 0) {
    readret = stream->read(stream->fd, buf, BUFSIZ);
    if (readret > 0) {
      if ((size_t)readret > total_size) {
        memcpy(cptr, buf, total_size);
        memcpy(stream->readbuf, buf + total_size, readret - total_size);
        stream->readbufcount = readret - total_size;
        break;
      } else {
        memcpy(cptr, buf, readret);
        total_size -= readret;
        if (readret < BUFSIZ) {
          stream->flags |= __STDIO_EOF;
          break;
        } else
          cptr += readret;
      }
    } else if (readret == 0) {
      stream->flags |= __STDIO_EOF;
      break;
    } else {
      stream->flags |= __STDIO_ERROR;
      break;
    }
  }
  return ts - total_size;
}
