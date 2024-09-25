#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __MACH__
extern int main(int, const char *[], const char *[], const char *[]);
#else
extern int main(int, const char *[], const char *[]);
#endif

int NXArgc = 0;
const char **NXArgv = NULL;
const char **environ = NULL;
const char *__progname = NULL;

void __cstart(int argc, const char *argv[], const char *envp[]) {
  NXArgc = argc;
  NXArgv = argv;
  environ = envp;

  if (argv[0] != NULL) {
    __progname = argv[0];
    const char *p;
    for (p = argv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  if (isatty(stdout->fd))
    stdout->flags |= __SLBF;
  char stdout_buf[stdout->bufsize];
  stdout->buf = stdout_buf;

#ifdef __MACH__
  const char **apple = envp;
  while (*apple != NULL)
    apple++;
  apple++;

  __stack_protect_init(apple);

  exit(main(argc, argv, envp, apple));
#else
  __stack_protect_init();

  exit(main(argc, argv, envp));
#endif
}
