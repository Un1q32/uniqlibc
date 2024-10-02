#include <stdio.h>
#include <unistd.h>

FILE __stdin = {STDIN_FILENO, __SRD, NULL, 0, 0, 0, read, write, lseek, close};

FILE *stdin = &__stdin;
