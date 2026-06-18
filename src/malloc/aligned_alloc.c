#include <errno.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

struct __heap **__heap_list = NULL;
size_t __heap_list_size = 0;

static bool realloc_heap_list(size_t old_size, size_t new_size) {
  struct __heap **ret = __internal_malloc(new_size);
  if (!ret)
    return false;
  if (old_size > 0) {
    memcpy(ret, __heap_list, old_size < new_size ? old_size : new_size);
    __internal_free(__heap_list);
  }
  __heap_list = ret;
  return true;
}

void *aligned_alloc(size_t alignment, size_t size) {
  /* ensure alignment is a power of 2 */
  if ((alignment & (alignment - 1)) != 0) {
    errno = EINVAL;
    return NULL;
  }

  /* avoid unaligned access */
  if (alignment < sizeof(void *))
    alignment = sizeof(void *);

  /* try to allocate from existing heaps */
  for (size_t i = __heap_list_size; i--;) {
    struct __heap *heap = __heap_list[i];
    /* see if there's space at the end of the heap */
    uintptr_t ptr = (uintptr_t)(heap->last) +
                    (sizeof(struct __malloc_block) * 2) + heap->last->size;
    /* overflow check */
    if (ptr < sizeof(struct __malloc_block))
      continue;
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0)
      continue;
    uintptr_t ptrsize = ptr + size;
    /* overflow check */
    if (ptrsize < ptr)
      continue;
    uintptr_t heap_end = (uintptr_t)heap + __internal_malloc_usable_size(heap);
    if (ptrsize < heap_end) {
      /* fit found */
      struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
      new_block->size = size;
      new_block->prev = heap->last;
      new_block->next = NULL;
      heap->last->next = new_block;
      heap->last = new_block;
      return (void *)ptr;
    }
  }

  /* stupid trick to avoid having to use goto */
  do {
    /* we grow __heap_list as needed */
    bool heap_list_grew = false;
    size_t heap_list_bytes = __internal_malloc_usable_size(__heap_list);
    if (heap_list_bytes < (__heap_list_size + 2) * sizeof(void *)) {
      /* allocate more space */
      if (!realloc_heap_list(heap_list_bytes,
                             heap_list_bytes + __HEAP_LIST_BLOCK_SIZE))
        return NULL;
      heap_list_grew = true;
    }

    /* allocate a new heap, with at least as much space as we need */
    size_t new_heap_size = size + alignment - 1;
    /* overflow check */
    if (new_heap_size < size) {
      if (heap_list_grew) /* shrink it back */
        realloc_heap_list(heap_list_bytes + __HEAP_LIST_BLOCK_SIZE,
                          heap_list_bytes);
      break;
    }
    new_heap_size += sizeof(struct __malloc_block);
    /* overflow check */
    if (new_heap_size < sizeof(struct __malloc_block)) {
      if (heap_list_grew) /* shrink it back */
        realloc_heap_list(heap_list_bytes + __HEAP_LIST_BLOCK_SIZE,
                          heap_list_bytes);
      break;
    }
    new_heap_size += sizeof(struct __heap);
    /* overflow check */
    if (new_heap_size < sizeof(struct __heap)) {
      if (heap_list_grew) /* shrink it back */
        realloc_heap_list(heap_list_bytes + __HEAP_LIST_BLOCK_SIZE,
                          heap_list_bytes);
      break;
    }

    /* round up to next multiple of heap block size if not already aligned */
    if ((new_heap_size & (__HEAP_BLOCK_SIZE - 1)) != 0)
      new_heap_size = (new_heap_size | (__HEAP_BLOCK_SIZE - 1)) + 1;

    /* allocate the heap */
    struct __heap *new_heap = __internal_malloc(new_heap_size);
    if (!new_heap) {
      if (heap_list_grew) /* shrink it back */
        realloc_heap_list(heap_list_bytes + __HEAP_LIST_BLOCK_SIZE,
                          heap_list_bytes);
      break;
    }
    ++__heap_list_size;
    new_heap->last = NULL;

    /* setup first block */
    uintptr_t ptr = (uintptr_t)new_heap + sizeof(struct __heap) +
                    sizeof(void *) + sizeof(struct __malloc_block);
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;

    struct __malloc_block *block = (struct __malloc_block *)ptr - 1;
    /* the first block has a pointer to the start of the heap behind it */
    ((struct __heap **)block)[-1] = new_heap;
    block->size = size;
    block->prev = NULL;
    block->next = NULL;

    new_heap->last = block;
    __heap_list[__heap_list_size - 1] = new_heap;
    __heap_list[__heap_list_size] = NULL;
    return block + 1;
  } while (0);

  /* try to allocate from existing heaps again, but this time look between the
   * gaps in allocations */
  for (size_t i = 0; __heap_list[i]; ++i) {
    struct __heap *heap = __heap_list[i];
    struct __malloc_block *block = heap->last;
    uintptr_t ptr;
    while (block->prev) {
      ptr = (uintptr_t)block->prev + (sizeof(struct __malloc_block) * 2) +
            block->prev->size;
      /* round up if not already aligned */
      if ((ptr & (alignment - 1)) != 0)
        ptr = (ptr | (alignment - 1)) + 1;
      /* overflow check */
      if (ptr == 0) {
        block = block->prev;
        continue;
      }
      uintptr_t ptrsize = ptr + size;
      /* overflow check */
      if (ptrsize < ptr) {
        block = block->prev;
        continue;
      }
      if (ptrsize < (uintptr_t)block) {
        /* fit found */
        struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
        new_block->size = size;
        new_block->prev = block->prev;
        new_block->next = block;
        block->prev->next = new_block;
        block->prev = new_block;
        return (void *)ptr;
      }
      block = block->prev;
    }

    /* see if there's space between the start of the heap and the first block */
    ptr = (uintptr_t)heap + sizeof(struct __heap) + sizeof(void *) +
          sizeof(struct __malloc_block);
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0)
      continue;
    uintptr_t ptrsize = ptr + size;
    /* overflow check */
    if (ptrsize < ptr)
      continue;
    if (ptrsize < (uintptr_t)block) {
      /* fit found */
      struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
      /* the first block has a pointer to the start of the heap behind it */
      ((struct __heap **)new_block)[-1] = heap;
      new_block->size = size;
      new_block->prev = NULL;
      new_block->next = block;
      block->prev = new_block;
      return (void *)ptr;
    }
  }

  errno = ENOMEM;
  return NULL;
}
