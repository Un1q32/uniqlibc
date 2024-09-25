#include <stdio.h>
#include <sys/mman.h>

void free(void *ptr) {
  if (ptr == NULL)
    return;

  ptr = (size_t *)ptr - 1;
  size_t size = *(size_t *)ptr;

#ifdef DEBUG
  if (munmap(ptr, size) == -1)
    perror("free()");
#else
  munmap(ptr, size);
#endif
}
