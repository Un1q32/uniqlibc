/*
 * This is the function every syscall goes through, first
 * argument is the syscall number, then syscall args. BSDs
 * have a special syscall that reorders the arguments for
 * us. Call the special syscall, then check if there was an
 * error by checking the carry bit, if there was an error,
 * jump to __syscall_error, else jump to __syscall_success.
 */

.globl _syscall
.align 2

_syscall:
#if defined(__arm__)
  mov r12, sp
  stmdb sp!, {r4, r5, r6, r8}
  ldmia r12, {r4, r5, r6}
  mov r12, #0
  swi 0x80
  ldmia sp!, {r4, r5, r6, r8}
  bcc ___syscall_success
  b ___syscall_error
#elif defined(__aarch64__)
  ldp x1, x2, [sp]
  ldp x3, x4, [sp, #0x10]
  ldp x5, x6, [sp, #0x20]
  ldr x7, [sp, #0x30]
  mov x16, #0
  svc #0x80
  b.lo 2f
  b ___syscall_error
2:
  b ___syscall_success
#elif defined(__x86_64__)
  mov $0x2000000, %eax
  mov %rcx, %r10
  syscall
  mov %rax, %rdi
  jb ___syscall_error
  mov %rdx, %rsi
  jmp ___syscall_success
#elif defined(__i386__)
  mov $0, %eax
  int $0x80
  mov %eax, -16(%esp)
  jc 2f
  sub $16, %esp
  mov %edx, 4(%esp)
  call ___syscall_success
  add $16, %esp
  ret
2:
  sub $16, %esp
  call ___syscall_error
  add $16, %esp
  ret
#elif defined(__powerpc__) || defined(__POWERPC__)
  li r0, 0
  sc
  b ___syscall_error
  b ___syscall_success
#else
#error architecture not supported
#endif

.subsections_via_symbols
