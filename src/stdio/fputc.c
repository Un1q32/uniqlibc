#include <stdio.h>

int fputc(int ch, FILE *stream) {
  if (!stream->write) {
    stream->flags |= __STDIO_ERROR;
    return EOF;
  }
  if (stream->flags & __STDIO_UNBUFFERED) {
    /*
     * If the stream is unbuffered, fwrite is just a
     * thin wrapper around the stream's write function.
     */
    ssize_t writeret = stream->write(stream->fd, &ch, 1);
    if (writeret < 0) {
      stream->flags |= __STDIO_ERROR;
      return EOF;
    }
  } else {
    if (!stream->writebuf) {
      stream->flags |= __STDIO_ERROR;
      return EOF;
    }
    /* If the stream's buffer is full, flush it */
    if (stream->writebufcount == stream->writebufsize)
      /* If fflush fails, return EOF */
      if (fflush(stream) != 0)
        return EOF;
    stream->writebuf[stream->writebufcount++] = ch;
    /* Line buffered streams are flushed when a newline is encountered */
    if (stream->flags & __STDIO_LINEBUFFERED && ch == '\n')
      /* If fflush fails, return EOF */
      if (fflush(stream) != 0)
        return EOF;
  }
  return ch;
}
