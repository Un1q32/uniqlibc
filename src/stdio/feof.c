#include <stdio.h>

int feof(FILE *stream) { return stream->flags & __STDIO_EOF; }
