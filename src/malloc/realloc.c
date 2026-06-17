#include <stdlib.h>
#include <string.h>

void *realloc(void *ptr, size_t size) {
  if (!ptr)
    return malloc(size);

  struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

  if (block->next) {
    /* check if there's already enough space before the next block */
    if ((uintptr_t)(block->next) - (uintptr_t)ptr >= size) {
      block->size = size;
      return ptr;
    }
  }

  void *new_ptr = malloc(size);
  if (!new_ptr)
    return NULL;

  memcpy(new_ptr, ptr, block->size < size ? block->size : size);
  free(ptr);
  return new_ptr;
}
