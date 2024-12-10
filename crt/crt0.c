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
 * It's purpose is to enter the __cstart function with the
 * initial stack pointer as the first arguement,
 * and sometimes align the stack to a 16 bit boundary.
 *
 * Note that __cstart is never really called, this function will just fall
 * through to it, not explicitly calling __cstart saves a jump instruction
 */

__asm__(".globl " START "\n" /* Make sure the start function is exported */
        START ":\n"          /* Mark the start of the function */
#if defined(__x86_64__)
        "mov %rsp, %rdi\n" /* Move inital stack pointer to first argument */
        "and $-16, %rsp\n" /* 16 bit align the stack */
        "push $0"          /* Push NULL as return address */
#elif defined(__i386__)
        "push %esp\n" /* Move inital stack pointer to first argument */
        "push $0"     /* Push NULL as return address */
#elif defined(__arm__)
        "mov r0, sp\n"     /* Move inital stack pointer to first argument */
        "bic sp, sp, 15\n" /* 16 bit align the stack */
#elif defined(__aarch64__)
        "mov x0, sp\n"       /* Move inital stack pointer to first argument */
        "and sp, x0, #~15\n" /* 16 bit align the stack */
#elif defined(__riscv)
        "mv a0, sp\n" /* Move inital stack pointer to first argument */
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

#ifdef FAKECRT
  (void)sp;
  int argc = 1;
  const char *argv[2] = {"a.out", NULL};
  const char **envp = argv + 1;
#else
  int argc = *(int *)sp;
  sp += sizeof(char *);
  const char **argv = (const char **)sp;
  sp += sizeof(char *) * (argc + 1);
  const char **envp = (const char **)sp;
#endif

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
