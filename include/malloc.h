#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __UNIQLIBC_PRIVATE_API
struct malloc_block {
  size_t size;
  struct malloc_block *prev;
  struct malloc_block *next;
};
#endif

__BEGIN_DECLS
extern void *malloc(size_t);
extern void *realloc(void *, size_t);
extern void *reallocf(void *, size_t);
extern void *reallocarray(void *, size_t, size_t);
extern void *calloc(size_t, size_t);
extern void free(void *);
extern size_t malloc_usable_size(void *);
extern void *aligned_alloc(size_t, size_t);
extern void *memalign(size_t, size_t);
extern int posix_memalign(void **, size_t, size_t);
extern void *valloc(size_t);
#ifdef __UNIQLIBC_PRIVATE_API
extern size_t heap_size;
extern struct malloc_block *heap_start;
#endif
__END_DECLS

#endif
