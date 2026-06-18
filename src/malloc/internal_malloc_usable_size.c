#include <stddef.h>

size_t __internal_malloc_usable_size(void *ptr) {
  if (!ptr)
    return 0;
  return *((size_t *)ptr - 1) - sizeof(size_t);
}
