#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

int fstat(int fd, struct stat *st) { return syscall(SYS_fstat, fd, st); }
