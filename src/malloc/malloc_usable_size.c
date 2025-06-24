#include <stddef.h>
#include <malloc.h>

size_t malloc_usable_size(void *ptr) {
  if (!ptr)
    return 0;
  return ((struct malloc_block *)ptr)[-1].size;
}
