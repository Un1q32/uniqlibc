/*
 * This is the first code ran when the program starts, it's
 * purpose is to call the __cstart function with the initial
 * stack pointer as the first argument, and align the stack.
 */

#if defined(__APPLE__)
#define START start
#define CSTART ___cstart
#else
#define START _start
#define CSTART __cstart
#if defined(__powerpc__) || defined(__POWERPC__)
#define r1 1
#define r3 3
#endif
#endif

.globl START
.align 2

START:
#if defined(__x86_64__)
  mov %rsp, %rdi    /* Move inital stack pointer to first argument */
  and $-16, %rsp    /* 16 byte align the stack */
  call CSTART       /* Call __cstart */
#elif defined(__i386__)
  mov %esp, %ebp    /* Store inital stack pointer to ebp */
  and $-16, %esp    /* 16 byte align the stack */
  sub $20, %esp     /* Make room for first argument, SSE aligned */
  mov %ebp, 4(%esp) /* Move inital stack pointer to first argument */
  jmp CSTART        /* Call __cstart */
#elif defined(__arm__)
  mov r0, sp        /* Move inital stack pointer to first argument */
  bic sp, sp, #15   /* 16 byte align the stack */
  b CSTART          /* Call __cstart */
#elif defined(__aarch64__)
  mov x0, sp        /* Move inital stack pointer to first argument */
  and sp, x0, #~15  /* 16 byte align the stack */
  b CSTART          /* Call __cstart */
#elif defined(__riscv)
  mv a0, sp         /* Move inital stack pointer to first argument */
  andi sp, sp, -16  /* 16 byte align the stack */
  j CSTART          /* Call __cstart */
#elif defined(__powerpc__) || defined(__POWERPC__)
  mr r3, r1         /* Move inital stack pointer to first argument */
  b CSTART          /* Call __cstart */
#else
#error architecture not supported
#endif

#if defined(__APPLE__)
.subsections_via_symbols
#else
.section .note.GNU-stack,"",%progbits
#endif
