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
  ssize_t readret;
  if (total_size >= BUFSIZ) {
    /* readsize is total_size rounded down to the last multiple of BUFSIZ */
    size_t readsize = total_size / BUFSIZ * BUFSIZ;
    readret = stream->read(stream->fd, cptr, readsize);
    if (readret < 0) {
      stream->flags |= __STDIO_ERROR;
      return (ts - total_size) / size;
    } else if ((size_t)readret == readsize) {
      total_size -= readret;
      cptr += readsize;
    } else {
      total_size -= readret;
      stream->flags |= __STDIO_EOF;
      return (ts - total_size) / size;
    }
  }
  if (total_size > 0) {
    char buf[BUFSIZ];
    readret = stream->read(stream->fd, buf, BUFSIZ);
    if (readret < 0)
      stream->flags |= __STDIO_ERROR;
    else if ((size_t)readret >= total_size) {
      memcpy(cptr, buf, total_size);
      memcpy(stream->readbuf, buf + total_size, readret - total_size);
      stream->readbufcount = readret - total_size;
      total_size = 0;
    } else {
      memcpy(cptr, buf, readret);
      stream->flags |= __STDIO_EOF;
      total_size -= readret;
    }
  }
  return (ts - total_size) / size;
}
