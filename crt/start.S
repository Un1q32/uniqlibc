#if defined(__x86_64__) || defined(__i386__)
.intel_syntax noprefix
#endif

#if defined(__ELF__)
#define START _start
#define CRT __cstart
#elif defined(__APPLE__)
#define START start
#define CRT ___cstart
#else
#error unsupported binary format
#endif

.globl START
.align 2

START:
#if defined(__linux__)
#if defined(__x86_64__)
  xor rbp, rbp
  pop rdi
  mov rsi, rsp
  and rsp, -16
  mov rdx, rdi
  add rdx, 1
  shl rdx, 3
  add rdx, rsi
  call CRT
  hlt
#elif defined(__i386__)
  xor ebp, ebp
  pop ecx
  mov edx, esp
  push ecx
  lea eax, [edx + ecx * 4 + 4]
  push eax
  push edx
  push ecx
  call CRT
  hlt
#else
#error architecture not supported
#endif
#elif defined(__FreeBSD__)
#if defined(__x86_64__)
  push rbp
  mov rbp, rsp
  mov rcx, rsi
  mov rsi, rdi
  add rsi, 8
  mov rdx, rdi
  add rdx, 16
  movsxd rax, dword ptr [rdi]
  mov edi, eax
  shl rax, 3
  add rdx, rax
  movabs r8, 0
  call CRT
  hlt
#elif defined(__i386__)
  pop esi
  mov edi, esp
  xor ebp, ebp
  push ebp
  mov ebp, esp
  and esp, -16
  sub esp, 12
  push 0
  push edx
  mov eax, edi
  mov ecx, esi
  shl ecx, 2
  add eax, ecx
  add eax, 4
  push eax
  push edi
  push esi
  call CRT
  hlt
#elif defined(__aarch64__)
  mov x3, x2
  add x1, x0, 8
  ldr x0, [x0]
  add x2, x1, x0, lsl #3
  add x2, x2, 8
  bl CRT
  udf 0
#elif defined(__arm__)
  ldr r0, [sp]
  add r1, sp, 4
  add r2, r1, r0, lsl #2
  add r2, r2, 4
  bic sp, sp, 7
  b CRT
#else
#error architecture not supported
#endif
#elif defined(__APPLE__)
#if defined(__arm__)
  ldr r0, [sp]
  add r1, sp, 4
  add r4, r0, 1
  add r2, r1, r4, lsl #2
  bic sp, sp, 15
  bl CRT
  .long 0xe1200070
#elif defined(__aarch64__)
  mov x5, sp
  ldr x0, [x5]
  add x1, x5, 8
  add x4, x0, 1
  add x2, x1, x4, lsl #3
  and sp, x5, #~15
  bl CRT
  brk 0
#elif defined(__x86_64__)
  push 0
  mov rbp, rsp
  and rsp, -16
  mov rdi, qword ptr [rbp + 8]
  lea rsi, [rbp + 16]
  mov edx, edi
  add edx, 1
  shl edx, 3
  add rdx, rsi
  call CRT
  hlt
#elif defined(__i386__)
  push 0
  mov ebp, esp
  and esp, -16
  sub esp, 16
  mov ebx, dword ptr [ebp + 4]
  mov dword ptr [esp], ebx
  lea ecx, [ebp + 8]
  mov dword ptr [esp + 4], ecx
  add ebx, 1
  shl ebx, 2
  add ebx, ecx
  mov dword ptr [esp + 8], ebx
  call CRT
  hlt
#elif defined(__ppc__)
  mr r26, r1
  subi r1, r1, 4
  clrrwi r1, r1, 5
  li r0, 0
  stw r0, 0(r1)
  stwu r1, -64(r1)
  lwz r3, 0(r26)
  addi r4, r26, 4
  addi r27, r3, 1
  slwi r27, r27, 2
  add r5, r4, r27
  bl CRT
  trap
#else
#error architecture not supported
#endif
#else
#error platform not supported
#endif

#if defined(__APPLE__) && !defined(__ELF__)
.subsections_via_symbols
#endif
