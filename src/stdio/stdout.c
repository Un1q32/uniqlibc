#include <stdio.h>
#include <unistd.h>

static char __stdout_buf[BUFSIZ];

static FILE __stdout = {
    '\0', __SWR, STDOUT_FILENO, __stdout_buf, NULL,  NULL, BUFSIZ, 0, 0,
    0,    0,     read,          write,        lseek, close};

FILE *stdout = &__stdout;
