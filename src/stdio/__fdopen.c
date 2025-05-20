#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *__fdopen(int fd, mode_t flags) {
  FILE *ret = malloc(sizeof(FILE));
  if (!ret)
    return NULL;

  if (flags & O_WRONLY) {
    ret->writebuf = malloc(BUFSIZ);
    if (!ret->writebuf) {
      free(ret);
      return NULL;
    }
    ret->readbuf = NULL;
    ret->write = write;
  } else if (flags & O_RDWR) {
    ret->writebuf = malloc(BUFSIZ);
    if (!ret->writebuf) {
      free(ret);
      return NULL;
    }
    ret->readbuf = malloc(BUFSIZ);
    if (!ret->readbuf) {
      free(ret->writebuf);
      free(ret);
      return NULL;
    }
    ret->read = read;
    ret->write = write;
  } else {
    ret->readbuf = malloc(BUFSIZ);
    if (!ret->readbuf) {
      free(ret);
      return NULL;
    }
    ret->writebuf = NULL;
    ret->read = read;
  }

  ret->fd = fd;
  ret->writebufsize = BUFSIZ;
  ret->writebufcount = 0;
  ret->ungetcchar = 0;
  ret->ungetcbuf = NULL;
  ret->ungetcbufcount = 0;
  ret->readbufcount = 0;
  ret->flags |= __STDIO_MALLOCED_WRITEBUF | __STDIO_MALLOCED_READBUF |
                __STDIO_MALLOCED_STREAM;
  ret->seek = lseek;
  ret->close = close;

  if (!__open_stream_list) {
    __open_stream_list = malloc(sizeof(FILE *) * 2);
    if (!__open_stream_list) {
      free(ret->writebuf);
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
      free(ret->writebuf);
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
