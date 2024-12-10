/*
 * This is the first function ran when the program starts.
 * It's purpose is to call the __cstart function with the
 * initial stack pointer as the first arguement,
 * and sometimes align the stack to a 16 bit boundary
 */

#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

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
  mov rdi, rsp     /* Move inital stack pointer to first arguement */
  and rsp, -16     /* 16 bit align the stack */
  call CRT         /* Call __cstart */
#elif defined(__i386__)
  push esp         /* Move inital stack pointer to first arguement */
  call CRT         /* Call __cstart */
#elif defined(__arm__)
  mov r0, sp       /* Move inital stack pointer to first arguement */
  bic sp, sp, 15   /* 16 bit align the stack */
  b CRT            /* Call __cstart */
#elif defined(__aarch64__)
  mov x0, sp       /* Move inital stack pointer to first arguement */
  and sp, x0, #~15 /* 16 bit align the stack */
  b CRT            /* Call __cstart */
#elif defined(__riscv)
  mv a0, sp        /* Move inital stack pointer to first arguement */
  j CRT            /* Call __cstart */
#else
#error architecture not supported
#endif

#if defined(__APPLE__) && !defined(__ELF__)
.subsections_via_symbols
#endif
