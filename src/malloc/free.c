#include <machine/param.h>
#include <malloc.h>
#include <stdint.h>
#ifdef __linux__
#include "linux-brk.h"
#else
#include <sys/mman.h>
#endif

void free(void *ptr) {
  if (!ptr)
    return;

  struct malloc_block *block = ptr;
  --block;

  if (block->next) {
    block->next->prev = block->prev;
    if (block->prev)
      block->prev->next = block->next;
    else /* this is the first block in the heap */
      *__heap_start = block->next;
    return;
  }

  if (block->prev) {
    block->prev->next = NULL;

    /* check if we can return memory to the kernel */
    uintptr_t heap_end = (uintptr_t)(block->prev) +
                         sizeof(struct malloc_block) + block->prev->size;
    /* align to page boundary */
    if ((heap_end & PAGE_MASK) != 0)
      heap_end = (heap_end | PAGE_MASK) + 1;
    size_t unmapsize = (uintptr_t)__heap_start + __heap_size - heap_end;
    if (unmapsize > 0) {
#ifdef __linux__
      linux_brk((void *)((uintptr_t)__heap_start + __heap_size - unmapsize));
#else
      munmap((void *)heap_end, unmapsize);
#endif
      __heap_size -= unmapsize;
    }
    return;
  }

  /* this is the last block in the heap, uninitalize the heap */
#ifdef __linux__
  linux_brk(__heap_start);
#else
  munmap(__heap_start, __heap_size);
#endif
  __heap_start = NULL;
  __heap_size = 0;
}
