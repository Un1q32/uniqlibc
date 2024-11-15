#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  int fds[2];
  int piperet = pipe(fds);
  if (piperet == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    return 1;
  }

  const char *data = "This is data piped from a child process!";
  size_t datalen = strlen(data) + 1;
  if (pid == 0) {
    close(fds[0]);
    write(fds[1], data, datalen);
  } else {
    close(fds[1]);
    char buf[datalen];
    read(fds[0], buf, datalen);
    puts(buf);
  }
  return 0;
}
