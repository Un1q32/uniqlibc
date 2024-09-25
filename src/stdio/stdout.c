#include <stdio.h>
#include <unistd.h>

FILE _stdout = {STDOUT_FILENO, __SWR, NULL, BUFSIZ, 0,
                false,         0,     read, write,  lseek};

FILE *stdout = &_stdout;
