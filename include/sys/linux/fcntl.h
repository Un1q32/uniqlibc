#ifndef _SYS_LINUX_FCNTL_H_
#define _SYS_LINUX_FCNTL_H_

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#ifdef __mips__
#define O_CREAT 0400
#define O_EXCL 02000
#define O_APPEND 0010
#define O_NONBLOCK 0200
#else
#define O_CREAT 0100
#define O_EXCL 0200
#define O_APPEND 02000
#define O_NONBLOCK 04000
#endif
#define O_TRUNC 01000
#define O_CLOEXEC 02000000
#if defined(__arm__) || defined(__aarch64__) || defined(__powerpc__) ||        \
    defined(__POWERPC__) || defined(__m68k__)
#define O_NOFOLLOW 0100000
#else
#define O_NOFOLLOW 0400000
#endif

#define AT_FDCWD -100
#define AT_REMOVEDIR 0x200

#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4

#define FD_CLOEXEC 1

#endif
