#include <stdio.h>

int ferror(FILE *stream) { return stream->flags & __STDIO_ERROR; }
