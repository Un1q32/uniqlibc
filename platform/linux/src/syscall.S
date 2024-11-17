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
  mov rsi, rdx
  jmp __syscall_end
#else
#error architecture not supported
#endif
