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
  mov x16, #0x0
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
  pop %ecx
  pop %eax
  push %ecx
  int $0x80
  mov %eax, (%esp)
  mov %edx, 4(%esp)
  push %ecx
  jc ___syscall_error
  jmp ___syscall_success
#elif defined(__powerpc__) || defined(__POWERPC__)
  li r0, 0
  sc
  b ___syscall_error
  b ___syscall_success
#else
#error architecture not supported
#endif

.subsections_via_symbols
