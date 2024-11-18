#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

#if defined(__ELF__)
#define START _start
#define CRT __cstart
#elif defined(__APPLE__)
#define START start
#define CRT ___cstart
#else
#error unsupported binary format
#endif

.globl START
.align 2

START:
#if defined(__x86_64__)
  mov rdi, rsp
  and rsp, -16
  call CRT
  hlt
#elif defined(__i386__)
  push esp
  call CRT
  hlt
#elif defined(__arm__)
  mov r0, sp
  bic sp, sp, 15
  b CRT
#elif defined(__aarch64__)
  mov x0, sp
  and sp, x0, #~15
  b CRT
#elif defined(__riscv)
  mv a0, sp
  j CRT
#else
#error architecture not supported
#endif

#if defined(__APPLE__) && !defined(__ELF__)
.subsections_via_symbols
#endif
