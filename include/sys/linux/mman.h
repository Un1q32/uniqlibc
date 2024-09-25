#ifndef _SYS_LINUX_MMAN_H_
#define _SYS_LINUX_MMAN_H_

#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define PROT_NONE 0x00
#define PROT_READ 0x01
#define PROT_WRITE 0x02
#define PROT_EXEC 0x04

#define MAP_SHARED 0x0001
#define MAP_PRIVATE 0x0002
#define MAP_FIXED 0x0010
#define MAP_NORESERVE 0x4000

#define MAP_FILE 0x00
#define MAP_ANON 0x20

#define MAP_ANONYMOUS MAP_ANON

#define MAP_FAILED ((void *)-1)

__BEGIN_DECLS
void *mmap(void *, size_t, int, int, int, off_t);
int munmap(void *, size_t);
__END_DECLS

#endif
