#include <stdio.h>

void clearerr(FILE *stream) { stream->flags &= ~(__STDIO_ERROR | __STDIO_EOF); }
