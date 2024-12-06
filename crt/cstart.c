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

void __cstart(const char *sp) {
  NXArgc = *(int *)sp;
  sp += sizeof(char *);
  NXArgv = (const char **)sp;
  sp += sizeof(char *) * (NXArgc + 1);
  environ = (const char **)sp;

  if (NXArgv[0] != NULL) {
    __progname = NXArgv[0];
    const char *p;
    for (p = NXArgv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  if (isatty(stdout->fd))
    stdout->flags |= __SLBF;
  char stdout_buf[stdout->bufsize];
  stdout->buf = stdout_buf;
  char stdin_buf[BUFSIZ];
  stdin->rbuf = stdin_buf;

#ifdef __MACH__
  const char **apple = environ;
  while (*apple != NULL)
    apple++;
  apple++;

  __stack_protect_init(apple);

  exit(main(NXArgc, NXArgv, environ, apple));
#else
  __stack_protect_init();

  exit(main(NXArgc, NXArgv, environ));
#endif
}
