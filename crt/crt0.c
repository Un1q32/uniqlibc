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

#ifdef __APPLE__
#define START "start"
#define CRT " ___cstart\n"
#else
#define START "_start"
#define CRT " __cstart\n"
#endif

/*
 * This is the first function ran when the program starts.
 * It's purpose is to call the __cstart function with the
 * initial stack pointer as the first arguement,
 * and sometimes align the stack to a 16 bit boundary
 */

__asm__(
".globl " START "\n"
START ":\n"
#if defined(__x86_64__)
  "mov %rsp, %rdi\n"   /* Move inital stack pointer to first arguement register */
  "and $-16, %rsp\n"   /* 16 bit align the stack */
  "call" CRT           /* Call __cstart */
#elif defined(__i386__)
  "push %esp\n"        /* Move inital stack pointer to first arguement register */
  "call" CRT           /* Call __cstart */
#elif defined(__arm__)
  "mov r0, sp\n"       /* Move inital stack pointer to first arguement register */
  "bic sp, sp, 15\n"   /* 16 bit align the stack */
  "b" CRT              /* Call __cstart */
#elif defined(__aarch64__)
  "mov x0, sp\n"       /* Move inital stack pointer to first arguement register */
  "and sp, x0, #~15\n" /* 16 bit align the stack */
  "b" CRT              /* Call __cstart */
#elif defined(__riscv)
  "mv a0, sp\n"        /* Move inital stack pointer to first arguement register */
  "j" CRT              /* Call __cstart */
#else
#error architecture not supported
#endif
);

/*
 * This function is the first real code run after the program starts, called by
 * the entry function It sets up argc, argv, and envp, a couple global
 * variables, sets the correct buffer mode for stdout, initializes the stack
 * protector guard, and calls main()
 */

void __cstart(const char *sp) {
  int argc = *(int *)sp;
  sp += sizeof(char *);
  const char **argv = (const char **)sp;
  sp += sizeof(char *) * (argc + 1);
  const char **envp = (const char **)sp;

  /* equivalent to basename(argv[0]) */
  if (argv[0] != NULL) {
    __progname = argv[0];
    const char *p;
    for (p = argv[0]; *p; p++)
      if (*p == '/')
        __progname = p + 1;
  } else
    __progname = "";

  /* if stdout is a terminal device it should be line buffered */
  if (isatty(stdout->fd))
    stdout->flags |= __SLBF;

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

  exit(main(argc, argv, envp, apple));
#else
  __stack_protect_init();

  exit(main(argc, argv, envp));
#endif
}
