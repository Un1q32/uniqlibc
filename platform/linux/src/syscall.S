.globl __syscall

__syscall:
#if defined(__x86_64__)
  mov 16(%rsp), %rax
  mov %rcx, %r10
  syscall
  mov %rax, %rdi
  mov %rdx, %rsi
  jmp __syscall_end
#elif defined(__i386__)
  push %ebp
  mov %esp, %ebp
  push %ebx
  push %edi
  push %esi
  mov 8(%ebp), %ebx
  mov 12(%ebp), %ecx
  mov 16(%ebp), %edx
  mov 20(%ebp), %esi
  mov 24(%ebp), %edi
  mov 36(%ebp), %eax
  mov 28(%ebp), %ebp
  int $0x80
  pop %esi
  pop %edi
  pop %ebx
  pop %ebp
  mov %eax, 4(%esp)
  mov %edx, 8(%esp)
  jmp __syscall_end
#elif defined(__arm__)
  mov r12, sp
  push {r4, r5, r6, r7}
  ldm r12, {r4-r7}
  swi #0
  pop {r4, r5, r6, r7}
  b __syscall_end
#elif defined(__aarch64__)
  mov x8, x7
  svc #0
  b __syscall_end
#elif defined(__riscv)
  ecall
  j __syscall_end
#else
#error architecture not supported
#endif
