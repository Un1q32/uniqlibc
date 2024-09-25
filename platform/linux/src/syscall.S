#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

.globl syscall

syscall:
#if defined(__x86_64__)
  mov rax, rdi
  mov rdi, rsi
  mov rsi, rdx
  mov rdx, rcx
  mov r10, r8
  mov r8, r9
  mov r9, [rsp + 8]
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
