#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int fseek(FILE *stream, long offset, int whence) {
  if (!stream->seek) {
    stream->flags |= __STDIO_ERROR;
    errno = ESPIPE;
    return -1;
  }
  if (whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
    errno = EINVAL;
    return -1;
  }
  fflush(stream);
  return stream->seek(stream->fd, offset, whence);
}
