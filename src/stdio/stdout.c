#include <stdio.h>
#include <unistd.h>

FILE __stdout = {'\0', __SWR, STDOUT_FILENO, NULL,  BUFSIZ, 0,    NULL,
                 0,    0,     read,          write, lseek,  close};

FILE *stdout = &__stdout;
