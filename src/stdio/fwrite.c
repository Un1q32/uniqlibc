#include <stdio.h>
#include <string.h>

size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb,
              FILE *restrict stream) {
  /* Fail if the stream is read only */
  if (!stream->write) {
    stream->flags |= __STDIO_ERROR;
    return 0;
  }
  if (stream->flags & __STDIO_UNBUFFERED) {
    /*
     * If the stream is unbuffered, fwrite is just a
     * thin wrapper around the stream's write function.
     */
    ssize_t writeret = stream->write(stream->fd, ptr, size * nmemb);
    if (writeret < 0) {
      stream->flags |= __STDIO_ERROR;
      return 0;
    }
    return writeret / size;
  } else {
    if (!stream->writebuf) {
      stream->flags |= __STDIO_ERROR;
      return 0;
    }
    const char *src = ptr;
    size_t s = size * nmemb;
    char *dst = stream->writebuf + stream->writebufcount;
    size_t bufsize = stream->writebufsize;
    if (stream->flags & __STDIO_LINEBUFFERED) {
      /* Line buffered streams are flushed when a newline is encountered */
      while (s) {
        /* If the stream's buffer is full, flush it to make room */
        if (stream->writebufcount == bufsize) {
          /* If fflush fails, return the number of items that were written */
          if (fflush(stream) != 0)
            return nmemb - (s / size);
          dst = stream->writebuf;
        }
        size_t towrite = bufsize - stream->writebufcount;
        if (s < towrite)
          towrite = s;
        char *newl = memchr(src, '\n', towrite);
        if (newl)
          towrite = newl - src + 1;
        memcpy(dst, src, towrite);
        stream->writebufcount += towrite;
        src += towrite;
        s -= towrite;
        /* flush the stream when a newline is encountered */
        if (newl) {
          if (fflush(stream) != 0)
            return nmemb - (s / size);
          dst = stream->writebuf;
        }
      }
    } else {
      /* Standard streams are only flushed when the buffer is full */
      while (s) {
        /* If the stream's buffer is full, flush it */
        if (stream->writebufcount == bufsize) {
          /* If fflush fails, return the number of items that were written */
          if (fflush(stream) != 0)
            return nmemb - (s / size);
          dst = stream->writebuf;
        }
        size_t towrite = bufsize - stream->writebufcount;
        if (s < towrite)
          towrite = s;
        memcpy(dst, src, towrite);
        stream->writebufcount += towrite;
        src += towrite;
        s -= towrite;
      }
    }
    return nmemb;
  }
}
