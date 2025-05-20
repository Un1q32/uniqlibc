#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream) {
  fflush(stream);
  int ret = 0;
  if (stream->close)
    ret = stream->close(stream->fd);
  if (stream->listpos > 0) {
    __open_stream_list[stream->listpos] = NULL;
    size_t nstreams = *(size_t *)__open_stream_list;
    if (stream->listpos == nstreams)
      while (nstreams > 0 && __open_stream_list[nstreams] == NULL)
        --nstreams;
    *(size_t *)__open_stream_list = nstreams;
    FILE **new_list =
        realloc(__open_stream_list, (nstreams + 1) * sizeof(FILE *));
    if (new_list)
      __open_stream_list = new_list;
  }

  if (stream->flags & __STDIO_MALLOCED_WRITEBUF)
    free(stream->buf);
  if (stream->flags & __STDIO_MALLOCED_READBUF)
    free(stream->rbuf);
  if (stream->flags & __STDIO_MALLOCED_STREAM)
    free(stream);

  return ret;
}
