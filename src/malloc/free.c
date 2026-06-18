#include <errno.h>
#include <stdlib.h>

void free(void *ptr) {
  if (!ptr)
    return;

  struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

  /* the first block has a pointer to the heap struct right behind it */
  struct __malloc_block *first_block = block;
  struct __heap *heap = ((struct __heap **)first_block)[-1];

  if (block->next) {
    block->next->prev = block->prev;
    if (block->prev)
      block->prev->next = block->next;
    else /* put the heap pointer right behind the next block */
      ((struct __heap **)block->next)[-1] = heap;
    return;
  }

  if (block->prev) {
    while (first_block->prev)
      first_block = first_block->prev;
    heap = ((struct __heap **)first_block)[-1];
    block->prev->next = NULL;
    heap->last = block->prev;
    return;
  }

  /* this is the last block in the heap, uninitalize the heap */
  __internal_free(heap);
  /* remove the entry from the heap list */
  size_t i = 0;
  while (__heap_list[i] != heap)
    ++i;
  __heap_list[i] = __heap_list[__heap_list_size - 1];
  __heap_list[__heap_list_size - 1] = NULL;
  --__heap_list_size;
}
