#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *__fdopen(int fd, mode_t flags) {
  FILE *ret = malloc(sizeof(FILE));
  if (!ret)
    return NULL;

  if (flags & O_WRONLY) {
    ret->buf = malloc(BUFSIZ);
    if (!ret->buf) {
      free(ret);
      return NULL;
    }
    ret->rbuf = NULL;
    ret->write = write;
  } else if (flags & O_RDWR) {
    ret->buf = malloc(BUFSIZ);
    if (!ret->buf) {
      free(ret);
      return NULL;
    }
    ret->rbuf = malloc(BUFSIZ);
    if (!ret->rbuf) {
      free(ret->buf);
      free(ret);
      return NULL;
    }
    ret->read = read;
    ret->write = write;
  } else {
    ret->rbuf = malloc(BUFSIZ);
    if (!ret->rbuf) {
      free(ret);
      return NULL;
    }
    ret->buf = NULL;
    ret->read = read;
  }

  ret->fd = fd;
  ret->bufsize = BUFSIZ;
  ret->bufcount = 0;
  ret->uchar = 0;
  ret->ubuf = NULL;
  ret->ubufcount = 0;
  ret->rbufcount = 0;
  ret->flags |= __STDIO_MALLOCED_WRITEBUF | __STDIO_MALLOCED_READBUF | __STDIO_MALLOCED_STREAM;
  ret->seek = lseek;
  ret->close = close;

  if (!__open_stream_list) {
    __open_stream_list = malloc(sizeof(FILE *) * 2);
    if (!__open_stream_list) {
      free(ret->buf);
      free(ret);
      return NULL;
    }

    *((size_t *)__open_stream_list) = 1;
    __open_stream_list[1] = ret;
    ret->listpos = 1;
  } else {
    FILE **new_list =
        realloc(__open_stream_list,
                sizeof(FILE *) * (*((size_t *)__open_stream_list) + 2));
    if (!new_list) {
      free(ret->buf);
      free(ret);
      return NULL;
    }
    __open_stream_list = new_list;
    size_t *nstreams = (size_t *)__open_stream_list;
    __open_stream_list[++*nstreams] = ret;
    ret->listpos = *nstreams;
  }

  if (flags & O_CLOEXEC) {
    fcntl(fd, F_SETFD, FD_CLOEXEC);
    flags &= ~O_CLOEXEC;
  }

  if (isatty(fd))
    ret->flags |= __STDIO_LINEBUFFERED;

  return ret;
}
