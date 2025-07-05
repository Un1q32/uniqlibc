.globl syscall

syscall:
#if defined(__x86_64__)
  mov %rdi, %rax
  mov %rsi, %rdi
  mov %rdx, %rsi
  mov %rcx, %rdx
  mov %r8, %r10
  mov %r9, %r8
  mov 0x8(%rsp), %r9
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
  mov 8(%ebp), %eax
  mov 12(%ebp), %ebx
  mov 16(%ebp), %ecx
  mov 20(%ebp), %edx
  mov 24(%ebp), %esi
  mov 28(%ebp), %edi
  mov 32(%ebp), %ebp
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
  push {r4-r7}
  mov r7, r0
  mov r0, r1
  mov r1, r2
  mov r2, r3
  ldm r12, {r3-r6}
  swi #0
  pop {r4-r7}
  b __syscall_end
#elif defined(__aarch64__)
  mov x8, x0
  mov x0, x1
  mov x1, x2
  mov x2, x3
  mov x3, x4
  mov x4, x5
  mov x5, x6
  svc #0
  b __syscall_end
#elif defined(__riscv)
  mv a7, a0
  mv a0, a1
  mv a1, a2
  mv a2, a3
  mv a3, a4
  mv a4, a5
  mv a5, a6
  ecall
  j __syscall_end
#elif defined(__powerpc__) || defined(__POWERPC__)
  mr 0, 3
  mr 3, 4
  mr 4, 5
  mr 5, 6
  mr 6, 7
  mr 7, 8
  mr 8, 9
#ifndef __LP64__
  mr 9, 10
#endif
  sc
  bnslr
  b __syscall_error
#else
#error architecture not supported
#endif
