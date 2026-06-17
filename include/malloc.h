#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __UNIQLIBC_PRIVATE_API
struct __malloc_block {
  size_t size;
  struct __malloc_block *prev;
  struct __malloc_block *next;
};

struct __heap {
  size_t size;
  struct __malloc_block *last;
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
extern struct __heap **__heap_list;
#endif
__END_DECLS

#endif
