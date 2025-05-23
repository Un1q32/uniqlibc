/*
 * This is the first function ran when the program starts.
 * It's purpose is to call the __cstart function with the
 * initial stack pointer as the first arguement,
 * and sometimes align the stack to a 16 bit boundary
 */

#if defined(__APPLE__)
#define START start
#define CRT ___cstart
#else
#define START _start
#define CRT __cstart
#endif

.globl START
.align 2

START:
#if defined(__x86_64__)
  mov %rsp, %rdi   /* Move inital stack pointer to first arguement */
  and $-16, %rsp   /* 16 bit align the stack */
  call CRT         /* Call __cstart */
#elif defined(__i386__)
  mov %esp, %ebp   /* Store inital stack pointer to ebp */
  and $-16, %esp   /* 16 bit align the stack */
  sub $16, %esp    /* Move stack down a little */
  push %ebp        /* Move inital stack pointer to first arguement */
  xor %ebp, %ebp   /* Zero ebp */
  call CRT         /* Call __cstart */
#elif defined(__arm__)
  mov r0, sp       /* Move inital stack pointer to first arguement */
  bic sp, sp, #15  /* 16 bit align the stack */
  b CRT            /* Call __cstart */
#elif defined(__aarch64__)
  mov x0, sp       /* Move inital stack pointer to first arguement */
  and sp, x0, #~15 /* 16 bit align the stack */
  b CRT            /* Call __cstart */
#elif defined(__riscv)
  mv a0, sp        /* Move inital stack pointer to first arguement */
  j CRT            /* Call __cstart */
#elif defined(__powerpc__) || defined(__POWERPC__)
#ifdef __APPLE__
  mr r3, r1        /* Move inital stack pointer to first arguement */
  stwu r1, -64(r1) /* Allocate stack frame */
#else
#error non-macos powerpc is currently unsupported
#endif
  b CRT            /* Call __cstart */
#else
#error architecture not supported
#endif

#if defined(__APPLE__)
.subsections_via_symbols
#endif
