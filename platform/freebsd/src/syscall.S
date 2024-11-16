#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

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
  mov eax, 0x0
  mov r10, rcx
  syscall
  mov rdi, rax
  jb __syscall_error
  mov rsi, rdx
  jmp __syscall_success
#elif defined(__i386__)
  pop ecx
  pop eax
  push ecx
  int 0x80
  mov dword ptr [esp], eax
  mov dword ptr [esp + 4], edx
  push ecx
  jc __syscall_error
  jmp __syscall_success
#else
#error architecture not supported
#endif
