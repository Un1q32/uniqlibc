#include <stdio.h>
#include <unistd.h>

FILE _stdin = {STDIN_FILENO, __SRD, NULL, 0, 0, false, 0, read, write, lseek};

FILE *stdin = &_stdin;
