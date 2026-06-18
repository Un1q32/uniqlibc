#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>

void __internal_free(void *ptr) {
  if (!ptr)
    return;

  ptr = (size_t *)ptr - 1;
  size_t size = *(size_t *)ptr;

  int err = errno;
  munmap(ptr, size);
  errno = err;
}
