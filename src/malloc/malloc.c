#include <malloc.h>

void *malloc(size_t size) { return aligned_alloc(16, size); }
