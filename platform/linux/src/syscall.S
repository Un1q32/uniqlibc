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
#elif defined(__i386__)
  push ebp
  mov ebp, esp
  push ebx
  push edi
  push esi
  mov ebx, [ebp + 8]
  mov ecx, [ebp + 12]
  mov edx, [ebp + 16]
  mov esi, [ebp + 20]
  mov edi, [ebp + 24]
  mov eax, [ebp + 36]
  mov ebp, [ebp + 28]
  int 0x80
  pop esi
  pop edi
  pop ebx
  pop ebp
  mov dword ptr [esp + 4], eax
  mov dword ptr [esp + 8], edx
  jmp __syscall_end
#elif defined(__arm__)
  push {r4, r5, r7}
  add r4, sp, 12
  ldm r4, {r4-r7}
  swi #0
  pop {r4, r5, r7}
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
