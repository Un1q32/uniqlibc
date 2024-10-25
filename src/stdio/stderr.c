#include <stdio.h>
#include <unistd.h>

FILE __stderr = {'\0', __SWR | __SNBF, STDERR_FILENO, NULL,  0,    0, NULL, 0,
                 0,    read,           write,         lseek, close};

FILE *stderr = &__stderr;
