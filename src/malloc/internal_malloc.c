#include <sys/mman.h>
#include <machine/param.h>
#include <errno.h>

void *__internal_malloc(size_t size) {
  size += sizeof(size_t);
  /* overflow check */
  if (size < sizeof(size_t)) {
    errno = ENOMEM;
    return NULL;
  }
  /* round up to multiple of page size */
  if ((size & PAGE_MASK) != 0)
    size = (size | PAGE_MASK) + 1;
  size_t *ptr =
      mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (ptr == MAP_FAILED)
    return NULL;

  ptr[0] = size;

  return ptr + 1;
}
