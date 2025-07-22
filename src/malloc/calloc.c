#include <errno.h>
#include <malloc.h>
#include <strings.h>

void *calloc(size_t count, size_t size) {
  size_t total_size = count * size;
  if (total_size / size != count) {
    errno = ENOMEM;
    return NULL;
  }
  void *ptr = malloc(total_size);
  if (!ptr)
    return NULL;

  bzero(ptr, total_size);
  return ptr;
}
