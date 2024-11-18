#include <sys/ioctl.h>

int isatty(int fd) {
  struct winsize wsz;
  return ioctl(fd, TIOCGWINSZ, &wsz) + 1;
}
