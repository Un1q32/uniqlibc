#include <string.h>

void *memset_explicit(void *buf, int c, size_t n) {
  memset(buf, c, n);
  __asm__ volatile("" : : "r"(buf) : "memory");
}
