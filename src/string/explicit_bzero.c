#include <strings.h>

void explicit_bzero(void *buf, size_t n) {
  bzero(buf, n);
  __asm__ volatile("" : : "r"(buf) : "memory");
}
