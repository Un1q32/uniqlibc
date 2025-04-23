#include <stdio.h>
#include <unistd.h>

static char __stdin_buf[BUFSIZ];

static FILE __stdin = {'\0', 0, STDIN_FILENO, NULL, __stdin_buf, NULL, 0, 0, 0,
                       0,    0, read,         NULL, lseek,       close};

FILE *stdin = &__stdin;
