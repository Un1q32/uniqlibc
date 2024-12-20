#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __MACH__
extern int main(int, const char *[], const char *[], const char *[]);
#else
extern int main(int, const char *[], const char *[]);
#endif

int NXArgc;
const char **NXArgv;
const char *__progname;
extern const char **environ;

/*
 * This function is the first real code run after the program starts, called by
 * the entry function It sets up argc, argv, and envp, a couple global
 * variables, sets the correct buffer mode for stdout, initializes the stack
 * protector guard, and calls main
 */

void __cstart(const char **sp) {
  int argc = *(int *)sp;
  sp += 1;
  const char **argv = sp;
  sp += argc + 1;
  const char **envp = sp;

  /* equivalent to basename(argv[0]) */
  if (argv[0] != NULL) {
    __progname = argv[0];
    const char *p;
    for (p = argv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  NXArgc = argc;
  NXArgv = argv;
  environ = envp;

#ifdef __MACH__
  /*
   * Darwin has an extra string array stored
   * after envp that gets passed to main
   */
  const char **apple = envp;
  while (*apple != NULL)
    apple++;
  apple++;

  /*
   * One of the strings in the Apple array
   * is used to initialize the stack guard
   */
  __stack_protect_init(apple);
#else
  __stack_protect_init();
#endif

  /* if stdout is a terminal device it should be line buffered */
  if (isatty(stdout->fd))
    stdout->flags |= __SLBF;

#ifdef __MACH__
  exit(main(argc, argv, envp, apple));
#else
  exit(main(argc, argv, envp));
#endif
}
