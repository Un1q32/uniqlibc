#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int main(int, char *[], char *[]);

/*
 * This function is the first real code run after the program starts, called
 * by the entry function It sets up argc, argv, and environ, sets the correct
 * buffer mode for stdout, and calls main
 */

void __cstart(char **sp) {
  int argc = *(int *)sp;
  sp += 1;
  char **argv = sp;
  sp += argc + 1;
  environ = sp;

  /* if stdout is a terminal device it should be line buffered */
  if (isatty(stdout->fd))
    stdout->flags |= __STDIO_LINEBUFFERED;

  exit(main(argc, argv, environ));
}
