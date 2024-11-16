#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

.globl __syscall

__syscall:
#if defined(__x86_64__)
  mov rax, [rsp + 16]
  mov r10, rcx
  syscall
  mov rdi, rax
  cmp rdi, 0
  jge success
  cmp rdi, -4095
  jb success
  neg rdi
  jmp __syscall_error
success:
  mov rsi, rdx
  jmp __syscall_success
#else
#error architecture not supported
#endif
