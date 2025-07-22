#include <errno.h>
#include <machine/param.h>
#include <malloc.h>
#include <stdint.h>
#ifdef __linux__
#include <sys/syscall.h>
#include <unistd.h>
static inline void *linux_brk(void *addr) {
  return (void *)syscall(SYS_brk, addr);
}
#else
#include <sys/mman.h>
#endif

void free(void *ptr) {
  if (!ptr)
    return;

  struct malloc_block *block = (struct malloc_block *)ptr - 1;

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
      int err = errno;
#ifdef __linux__
      char *new_brk = linux_brk(
          (void *)((uintptr_t)__heap_start + __heap_size - unmapsize));
      __heap_size = new_brk - (char *)__heap_start;
#else
      munmap((void *)heap_end, unmapsize);
      __heap_size -= unmapsize;
#endif
      errno = err;
    }
    return;
  }

  /* this is the last block in the heap, uninitalize the heap */
  int err = errno;
#ifdef __linux__
  linux_brk(__heap_start);
#else
  munmap(__heap_start, __heap_size);
#endif
  errno = err;
  __heap_start = NULL;
  __heap_size = 0;
}
