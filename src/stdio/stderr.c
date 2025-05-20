#include <stdio.h>
#include <unistd.h>

static FILE __stderr = {'\0',
                        __STDIO_UNBUFFERED,
                        STDERR_FILENO,
                        NULL,
                        NULL,
                        NULL,
                        0,
                        0,
                        0,
                        0,
                        0,
                        NULL,
                        write,
                        lseek,
                        close};

FILE *stderr = &__stderr;
