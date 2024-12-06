#include <stdio.h>
#include <unistd.h>

char __stdin_buf[BUFSIZ];

FILE __stdin = {'\0', __SRD, STDIN_FILENO, NULL,  __stdin_buf, NULL, 0, 0, 0,
                0,    0,     read,         write, lseek,       close};

FILE *stdin = &__stdin;
