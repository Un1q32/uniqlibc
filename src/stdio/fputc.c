#include <stdio.h>

int fputc(int ch, FILE *stream) {
  if (!stream->write) {
    stream->flags |= __SERR;
    return EOF;
  }
  if (stream->flags & __SNBF) {
    /*
     * If the stream is unbuffered, fwrite is just a
     * thin wrapper around the stream's write function.
     */
    ssize_t writeret = stream->write(stream->fd, &ch, 1);
    if (writeret < 0) {
      stream->flags |= __SERR;
      return EOF;
    }
  } else {
    if (!stream->buf) {
      stream->flags |= __SERR;
      return EOF;
    }
    /* If the stream's buffer is full, flush it */
    if (stream->bufcount == stream->bufsize)
      /* If fflush fails, return EOF */
      if (fflush(stream) != 0)
        return EOF;
    stream->buf[stream->bufcount++] = ch;
    /* Line buffered streams are flushed when a newline is encountered */
    if (stream->flags & __SLBF && ch == '\n')
      /* If fflush fails, return EOF */
      if (fflush(stream) != 0)
        return EOF;
  }
  return ch;
}
