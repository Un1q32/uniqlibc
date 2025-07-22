#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(void) {
  void *ptr = aligned_alloc(4096, 16);
  assert(ptr && ((uintptr_t)ptr % 4096) == 0);

  void *ptr2 = aligned_alloc(16, 16);
  assert(ptr2 && ((uintptr_t)ptr2 % 16) == 0);

  void *ptr3 = aligned_alloc(32, 8192);
  assert(ptr3 && ((uintptr_t)ptr3 % 32) == 0);

  void *ptr4 = aligned_alloc(64, 50000);
  assert(ptr4 && ((uintptr_t)ptr4 % 64) == 0);

  void *ptr5 = aligned_alloc(16, 300);
  assert(ptr5 && ((uintptr_t)ptr5 % 16) == 0);

  bzero(ptr, 16);
  bzero(ptr2, 16);
  bzero(ptr3, 8192);
  bzero(ptr4, 50000);
  bzero(ptr5, 300);

  void *ptr6 = malloc(SIZE_MAX);

  free(ptr5);
  free(ptr4);
  free(ptr3);
  free(ptr2);
  free(ptr);

  assert(!ptr6 && errno == ENOMEM);

  puts("alloc test succeeded");

  return 0;
}
