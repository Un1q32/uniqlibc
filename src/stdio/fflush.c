#include <stdbool.h>
#include <stdio.h>

int fflush(FILE *stream) {
  if (!stream) {
    bool error = false;
    if (__open_stream_list) {
      size_t i = *((size_t *)__open_stream_list);
      while (i) {
        if (__open_stream_list[i])
          if (fflush(__open_stream_list[i]) != 0)
            error = true;
        i--;
      }
    }
    if (fflush(stdin) != 0)
      error = true;
    if (fflush(stdout) != 0)
      error = true;
    if (fflush(stderr) != 0)
      error = true;
    if (error)
      return EOF;
    return 0;
  }
  if (stream->write) {
    if (!stream->writebufcount)
      return 0;
    ssize_t writeret =
        stream->write(stream->fd, stream->writebuf, stream->writebufcount);
    if (writeret == -1 || (size_t)writeret != stream->writebufcount) {
      stream->flags |= __STDIO_ERROR;
      return EOF;
    } else
      stream->writebufcount = 0;
  }
  return 0;
}
