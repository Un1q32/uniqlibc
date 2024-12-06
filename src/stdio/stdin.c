#include <stdio.h>
#include <unistd.h>

FILE __stdin = {'\0', __SRD, STDIN_FILENO, NULL,  NULL,  NULL, 0, 0, 0,
                0,    0,     read,         write, lseek, close};

FILE *stdin = &__stdin;
