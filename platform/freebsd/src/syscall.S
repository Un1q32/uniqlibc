.globl syscall

syscall:
#if defined(__arm__)
  mov r12, r7
  mov r7, 0
  svc #0x0
  mov r7, r12
  bcc __syscall_success
  b __syscall_error
#elif defined(__aarch64__)
  mov x8, 0
  svc #0x0
  b.lo 2f
  b __syscall_error
2:
  b __syscall_success
#elif defined(__x86_64__)
  mov $0, %eax
  mov %rcx, %r10
  syscall
  mov %rax, %rdi
  jb __syscall_error
  mov %rdx, %rsi
  jmp __syscall_success
#elif defined(__i386__)
  pop %ecx
  pop %eax
  push %ecx
  int $0x80
  mov %eax, (%esp)
  mov %edx, 0x4(%esp)
  push %ecx
  jc __syscall_error
  jmp __syscall_success
#elif defined(__riscv)
  li t0, 0
  ecall
  bnez t0, error
  j __syscall_success
error:
  j __syscall_error
#else
#error architecture not supported
#endif
