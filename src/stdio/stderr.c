#include <stdio.h>
#include <unistd.h>

FILE __stderr = {STDERR_FILENO, __SWR | __SNBF, NULL,  0,    0, false, false, 0,
                 read,          write,          lseek, close};

FILE *stderr = &__stderr;
