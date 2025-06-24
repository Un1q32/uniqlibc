#include <errno.h>
#include <malloc.h>

int posix_memalign(void **memptr, size_t alignment, size_t size) {
  if (alignment < sizeof(void *))
    return EINVAL;
  void *ptr = aligned_alloc(alignment, size);
  if (!ptr)
    return errno;
  *memptr = ptr;
  return 0;
}
