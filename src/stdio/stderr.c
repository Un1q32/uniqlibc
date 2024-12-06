#include <stdio.h>
#include <unistd.h>

FILE __stderr = {
    '\0', __SWR | __SNBF, STDERR_FILENO, NULL,  NULL, NULL, 0, 0, 0, 0,
    0,    read,           write,         lseek, close};

FILE *stderr = &__stderr;
