#include <stdio.h>
#include <unistd.h>

static char __stdout_buf[BUFSIZ];

static FILE __stdout = {
    '\0', 0, STDOUT_FILENO, __stdout_buf, NULL,  NULL, BUFSIZ, 0, 0,
    0,    0, NULL,          write,        lseek, close};

FILE *stdout = &__stdout;
