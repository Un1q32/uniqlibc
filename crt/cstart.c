#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __MACH__
extern int main(int, const char *[], const char *[], const char *[]);
#else
extern int main(int, const char *[], const char *[]);
#endif

extern const char **environ;

/*
 * This function is the first real code run after the program starts, called by
 * the entry function It sets up argc, argv, and environ, a couple global
 * variables, sets the correct buffer mode for stdout, initializes the stack
 * protector guard, and calls main
 */

void __cstart(const char **sp) {
  int argc = *(int *)sp;
  sp += 1;
  const char **argv = sp;
  sp += argc + 1;
  environ = sp;

#ifdef __MACH__
  /*
   * Darwin has an extra string array stored
   * after environ that gets passed to main
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
#else
  __stack_protect_init();
#endif

  /* if stdout is a terminal device it should be line buffered */
  if (isatty(stdout->fd))
    stdout->flags |= __STDIO_LINEBUFFERED;

#ifdef __MACH__
  exit(main(argc, argv, environ, apple));
#else
  exit(main(argc, argv, environ));
#endif
}
