#include <stdio.h>
#include <unistd.h>

FILE _stderr = {STDERR_FILENO, __SWR | __SNBF, NULL, 0, 0, false, 0,
                read,          write,          lseek};

FILE *stderr = &_stderr;
