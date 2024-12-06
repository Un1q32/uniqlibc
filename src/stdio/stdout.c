#include <stdio.h>
#include <unistd.h>

FILE __stdout = {'\0', __SWR, STDOUT_FILENO, NULL,  NULL,  NULL, BUFSIZ, 0, 0,
                 0,    0,     read,          write, lseek, close};

FILE *stdout = &__stdout;
