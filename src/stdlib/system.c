#include <sys/wait.h>
#include <unistd.h>

int system(const char *command) {
  if (command == NULL) {
    if (access("/bin/sh", X_OK) == 0)
      return 1;
    else
      return 0;
  }
  pid_t pid = fork();
  if (pid == 0) {
    execl("/bin/sh", "sh", "-c", command, NULL);
    _exit(127);
  } else if (pid > 0) {
    int status;
    if (waitpid(pid, &status, 0) == -1)
      return -1;
    return status >> 8;
  }
  return -1;
}
