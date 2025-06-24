#include <malloc.h>

void *memalign(size_t alignment, size_t size) {
  return aligned_alloc(alignment, size);
}
