#include <errno.h>
#include <machine/param.h>
#include <stdlib.h>
#include <sys/mman.h>

void free(void *ptr) {
  if (!ptr)
    return;

  struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

  if (block->next) {
    block->next->prev = block->prev;
    if (block->prev)
      block->prev->next = block->next;
    return;
  }

  /* the first block has a pointer to the heap struct right behind it */
  struct __malloc_block *first_block = block;
  while (first_block->prev)
    first_block = first_block->prev;
  struct __heap *heap = ((struct __heap **)first_block)[-1];

  if (block->prev) {
    block->prev->next = NULL;
    heap->last = block->prev;

    /* check if we can return memory to the kernel */
    uintptr_t heap_end = (uintptr_t)(block->prev) +
                         sizeof(struct __malloc_block) + block->prev->size;
    /* align to page boundary */
    if ((heap_end & PAGE_MASK) != 0)
      heap_end = (heap_end | PAGE_MASK) + 1;
    size_t unmapsize = (uintptr_t)heap + heap->size - heap_end;
    if (unmapsize > 0) {
      int err = errno;
      munmap((void *)heap_end, unmapsize);
      heap->size -= unmapsize;
      errno = err;
    }
    return;
  }

  /* this is the last block in the heap, uninitalize the heap */
  int err = errno;
  munmap(heap, heap->size);
  errno = err;
  /* remove the entry from the heap list */
  size_t i = 0;
  while (__heap_list[i] != heap)
    ++i;
  __heap_list[__heap_list_size - 1] = __heap_list[__heap_list_size - 1];
  __heap_list[__heap_list_size - 1] = NULL;
  --__heap_list_size;
  /* check if we need to shrink the heap list */
  uintptr_t heap_list_end = (uintptr_t)(__heap_list + __heap_list_size);
  if (heap_list_end % PAGE_SIZE == 0)
    munmap((void *)heap_list_end, PAGE_SIZE);
}
