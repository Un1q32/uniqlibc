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

/*
 * This function is the first real code run after the program starts, called by
 * the entry function It sets up argc, argv, and envp, a couple other global
 * variables, sets the correct buffer mode for stdout, initializes the stack
 * protector guard, and calls main()
 */

void __cstart(const char *sp) {
  NXArgc = *(int *)sp;
  sp += sizeof(char *);
  NXArgv = (const char **)sp;
  sp += sizeof(char *) * (NXArgc + 1);
  environ = (const char **)sp;

  /* equivalent to basename(argv[0]) */
  if (NXArgv[0] != NULL) {
    __progname = NXArgv[0];
    const char *p;
    for (p = NXArgv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  /* if stdout is a terminal device it should be line buffered */
  if (isatty(stdout->fd))
    stdout->flags |= __SLBF;

#ifdef __MACH__
  /*
   * Darwin has an extra string array stored
   * after envp that gets passed to main
   */
  const char **apple = environ;
  while (*apple != NULL)
    apple++;
  apple++;

  /*
   * One of the strings in the Apple array
   * is used to initialize the stack guard
   */
  __stack_protect_init(apple);

  exit(main(NXArgc, NXArgv, environ, apple));
#else
  __stack_protect_init();

  exit(main(NXArgc, NXArgv, environ));
#endif
}
