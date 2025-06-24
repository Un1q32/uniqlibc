#include <machine/param.h>
#include <malloc.h>

void *valloc(size_t size) { return aligned_alloc(PAGE_SIZE, size); }
