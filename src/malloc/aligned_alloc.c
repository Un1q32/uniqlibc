#include <errno.h>
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
struct __malloc_block **__heap_start = NULL;

static bool expand_heap(size_t size) {
  /* round up to next multiple of page size if not already aligned */
  if ((size & PAGE_MASK) != 0)
    size = (size | PAGE_MASK) + 1;
  /* overflow check */
  if (size == 0)
    return false;

  if (!__heap_start) {
    /* allocate a new heap size bytes big */
#ifdef __linux__
    void *new_heap = linux_brk(NULL);
    /* overflow check */
    if ((uintptr_t)new_heap + size < (uintptr_t)new_heap)
      return false;
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
    /* overflow check */
    char *heap_end = (char *)__heap_start + __heap_size;
    if ((uintptr_t)heap_end + size < (uintptr_t)heap_end)
      return false;

    /* expand the heap by size bytes */
#ifdef __linux__
    void *more_heap = linux_brk(heap_end + size);
    if (more_heap != heap_end + size) {
      linux_brk(heap_end);
      return false;
    }
#else
    void *more_heap = mmap(heap_end, size, PROT_READ | PROT_WRITE,
                           MAP_PRIVATE | MAP_ANON | MAP_FIXED, -1, 0);
    if (more_heap == MAP_FAILED)
      return false;
#endif

    __heap_size += size;
  }
  return true;
}

static void uninitialize_heap(void) {
#ifdef __linux__
  linux_brk(__heap_start);
#else
  munmap(__heap_start, __heap_size);
#endif
  __heap_start = NULL;
  __heap_size = 0;
}

/* first fit aligned_alloc */
void *aligned_alloc(size_t alignment, size_t size) {
  /* ensure alignment is a power of 2 */
  if (alignment > 0 && (alignment & (alignment - 1)) != 0) {
    errno = EINVAL;
    return NULL;
  }

  /* avoid unaligned access */
  if (alignment < sizeof(void *))
    alignment = sizeof(void *);

  /* initialize the heap if it isn't already */
  if (!__heap_start) {
    size_t new_heap_size = size + alignment - 1;
    /* overflow check */
    if (new_heap_size < size) {
      errno = ENOMEM;
      return NULL;
    }
    new_heap_size += sizeof(struct __malloc_block);
    /* overflow check */
    if (new_heap_size < sizeof(struct __malloc_block)) {
      errno = ENOMEM;
      return NULL;
    }

    if (!expand_heap(new_heap_size)) {
      errno = ENOMEM;
      return NULL;
    }

    /* setup first block */
    uintptr_t ptr = (uintptr_t)__heap_start + sizeof(void *);
    /* overflow check */
    if (ptr < sizeof(void *)) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }
    ptr += sizeof(struct __malloc_block);
    /* overflow check */
    if (ptr < sizeof(struct __malloc_block)) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0) {
      uninitialize_heap();
      errno = ENOMEM;
      return NULL;
    }

    struct __malloc_block *block = (struct __malloc_block *)ptr - 1;

    block->size = size;
    block->prev = NULL;
    block->next = NULL;

    /* the heap start has a pointer to the first block */
    *__heap_start = block;

    return block + 1;
  }

  /* see if there's space at the start of the heap */
  struct __malloc_block *block = *__heap_start;
  uintptr_t ptr =
      (uintptr_t)__heap_start + sizeof(void *) + sizeof(struct __malloc_block);
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  /* overflow check */
  if (ptr == 0) {
    errno = ENOMEM;
    return NULL;
  }
  uintptr_t ptrsize = ptr + size;
  /* overflow check */
  if (ptrsize < ptr) {
    errno = ENOMEM;
    return NULL;
  }
  if (ptrsize < (uintptr_t)block) {
    /* fit found */
    struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
    new_block->size = size;
    new_block->prev = NULL;
    new_block->next = block;
    block->prev = new_block;
    *__heap_start = new_block;
    return (void *)ptr;
  }

  /* see if there's space between blocks */
  while (block->next) {
    ptr = (uintptr_t)block + (sizeof(struct __malloc_block) * 2) + block->size;
    /* overflow check */
    if (ptr < sizeof(struct __malloc_block)) {
      errno = ENOMEM;
      return NULL;
    }
    /* round up if not already aligned */
    if ((ptr & (alignment - 1)) != 0)
      ptr = (ptr | (alignment - 1)) + 1;
    /* overflow check */
    if (ptr == 0) {
      errno = ENOMEM;
      return NULL;
    }
    ptrsize = ptr + size;
    /* overflow check */
    if (ptrsize < ptr) {
      errno = ENOMEM;
      return NULL;
    }
    if (ptrsize < (uintptr_t)(block->next)) {
      /* fit found */
      struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
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
  ptr = (uintptr_t)block + (sizeof(struct __malloc_block) * 2) + block->size;
  /* overflow check */
  if (ptr < sizeof(struct __malloc_block)) {
    errno = ENOMEM;
    return NULL;
  }
  /* round up if not already aligned */
  if ((ptr & (alignment - 1)) != 0)
    ptr = (ptr | (alignment - 1)) + 1;
  /* overflow check */
  if (ptr == 0) {
    errno = ENOMEM;
    return NULL;
  }
  ptrsize = ptr + size;
  /* overflow check */
  if (ptrsize < ptr) {
    errno = ENOMEM;
    return NULL;
  }
  uintptr_t heap_end = (uintptr_t)__heap_start + __heap_size;
  if (ptrsize < heap_end) {
    /* fit found */
    struct __malloc_block *new_block = (struct __malloc_block *)ptr - 1;
    new_block->size = size;
    new_block->prev = block;
    new_block->next = NULL;
    block->next = new_block;
    return (void *)ptr;
  }

  /* no space was found, must request more memory from the kernel */
  if (!expand_heap(ptrsize - heap_end)) {
    errno = ENOMEM;
    return NULL;
  }

  struct __malloc_block *new_block =
      (struct __malloc_block *)(ptr - sizeof(struct __malloc_block));
  new_block->size = size;
  new_block->prev = block;
  new_block->next = NULL;
  block->next = new_block;
  return (void *)ptr;
}
