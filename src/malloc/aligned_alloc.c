#include <machine/param.h>
#include <malloc.h>
#include <stdbool.h>
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

size_t __heap_size = 0;
struct malloc_block **__heap_start = NULL;

static bool expand_heap(size_t size) {
  /* round up to next multiple of page size if not already aligned */
  if ((size & PAGE_MASK) != 0)
    size = (size | PAGE_MASK) + 1;

  if (!__heap_start) {
    /* allocate a new heap size bytes big */
#ifdef __linux__
    void *new_heap = linux_brk(NULL);
    void *new_end = linux_brk((char *)new_heap + size);
    if (new_end != (char *)new_heap + size) {
      linux_brk(new_heap);
      return false;
    }
#else
    void *new_heap =
        mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (new_heap == MAP_FAILED)
      return false;
#endif

    __heap_start = new_heap;
    __heap_size = size;
  } else {
    /* expand the heap by size bytes */
#ifdef __linux__
    void *more_heap = linux_brk((char *)__heap_start + __heap_size + size);
    if (more_heap != (char *)__heap_start + __heap_size + size) {
      linux_brk((char *)__heap_start + __heap_size);
      return false;
    }
#else
    void *more_heap =
        mmap((char *)__heap_start + __heap_size, size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANON | MAP_FIXED, -1, 0);
    if (more_heap == MAP_FAILED)
      return false;
#endif

    __heap_size += size;
  }
  return true;
}

/* first fit aligned_alloc */
void *aligned_alloc(size_t alignment, size_t size) {
  /* ensure alignment is a power of 2 */
  if (alignment > 0 && (alignment & (alignment - 1)) != 0)
    return NULL;

  /* initialize the heap if it isn't already */
  if (!__heap_start) {
    if (!expand_heap(size + alignment + sizeof(struct malloc_block)))
      return NULL;

    /* align the pointer */
    struct malloc_block *block =
        (struct malloc_block *)((((uintptr_t)__heap_start + sizeof(void *) +
                                  sizeof(struct malloc_block)) |
                                 (alignment - 1)) +
                                1 - sizeof(struct malloc_block));

    block->size = size;
    block->prev = NULL;
    block->next = NULL;

    /* the heap start has a pointer to the first block */
    *__heap_start = block;

    return block + 1;
  }

  /* see if there's space at the start of the heap */
  struct malloc_block *block = *__heap_start;
  uintptr_t ptr =
      (uintptr_t)__heap_start + sizeof(void *) + sizeof(struct malloc_block);
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  if (ptr + size < (uintptr_t)block) {
    /* fit found */
    struct malloc_block *new_block =
        (struct malloc_block *)(ptr - sizeof(struct malloc_block));
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = block;
    block->prev = new_block;
    *__heap_start = new_block;
    return (void *)ptr;
  }

  /* see if there's space between blocks */
  while (block->next) {
    ptr = (uintptr_t)block + (sizeof(struct malloc_block) * 2) + block->size;
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    if (ptr + size < (uintptr_t)(block->next)) {
      /* fit found */
      struct malloc_block *new_block =
          (struct malloc_block *)(ptr - sizeof(struct malloc_block));
      new_block->size = size;
      new_block->prev = block;
      new_block->next = block->next;
      block->next->prev = new_block;
      block->next = new_block;
      return (void *)ptr;
    }
    block = block->next;
  }

  /* see if there's space at the end of the heap */
  ptr = (uintptr_t)block + (sizeof(struct malloc_block) * 2) + block->size;
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  if (ptr + size < (uintptr_t)__heap_start + __heap_size) {
    /* fit found */
    struct malloc_block *new_block =
        (struct malloc_block *)(ptr - sizeof(struct malloc_block));
    new_block->size = size;
    new_block->prev = block;
    new_block->next = NULL;
    block->next = new_block;
    return (void *)ptr;
  }

  /* no space was found, must request more memory from the kernel */
  if (!expand_heap((ptr + size) - ((uintptr_t)__heap_start + __heap_size)))
    return NULL;

  struct malloc_block *new_block =
      (struct malloc_block *)(ptr - sizeof(struct malloc_block));
  new_block->size = size;
  new_block->prev = block;
  new_block->next = NULL;
  block->next = new_block;
  return (void *)ptr;
}
