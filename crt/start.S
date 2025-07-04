/*
 * This is the first function ran when the program starts.
 * It's purpose is to call the __cstart function
 * with the initial stack pointer as the first argument,
 * and sometimes align the stack
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
  sub $16, %esp     /* Make room for first argument, SSE aligned */
  mov %ebp, 0(%esp) /* Move inital stack pointer to first argument */
  xor %ebp, %ebp    /* Zero ebp */
  call CSTART       /* Call __cstart */
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
  j CSTART          /* Call __cstart */
#elif defined(__powerpc__) || defined(__POWERPC__)
  mr r3, r1         /* Move inital stack pointer to first argument */
  clrrdi r1, r1, 5  /* 32 byte align the stack */
  stwu r1, -64(r1)  /* Allocate stack frame */
  b CSTART          /* Call __cstart */
#else
#error architecture not supported
#endif

#if defined(__APPLE__)
.subsections_via_symbols
#endif
