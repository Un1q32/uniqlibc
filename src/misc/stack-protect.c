#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __MACH__
#include <string.h>
#endif

#ifdef __LP64__
unsigned long __stack_chk_guard = 0xDEADDEADDEADDEAD;
#else
unsigned long __stack_chk_guard = 0xDEADDEAD;
#endif

void __stack_chk_fail(void) {
  static const char msg[] = "Stack smashing detected!\n";
  fwrite(msg, 1, sizeof(msg) - 1, stderr);
  abort();
}

void __stack_chk_fail_local(void) { __stack_chk_fail(); }

#ifdef __MACH__
void __stack_protect_init(const char *apple[]) {
  size_t i = 0;
  while (apple[i]) {
    if (strncmp(apple[i], "stack_guard=0x", 14) == 0) {
      __stack_chk_guard = strtoul(apple[i] + 14, NULL, 16);
      break;
    }
    i++;
  }
  if (!apple[i])
#else
void __stack_protect_init(void) {
#endif
    arc4random_buf(&__stack_chk_guard, sizeof(__stack_chk_guard));
}
