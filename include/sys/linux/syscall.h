#ifndef _SYS_LINUX_SYSCALL_H_
#define _SYS_LINUX_SYSCALL_H_

#if defined(__x86_64__)
#define SYS_read 0
#define SYS_write 1
#define SYS_open 2
#define SYS_close 3
#define SYS_stat 4
#define SYS_fstat 5
#define SYS_lseek 8
#define SYS_mmap 9
#define SYS_munmap 11
#define SYS_rt_sigaction 13
#define SYS_ioctl 16
#define SYS_pipe 22
#define SYS_dup 32
#define SYS_dup2 33
#define SYS_nanosleep 35
#define SYS_getpid 39
#define SYS_fork 57
#define SYS_vfork 58
#define SYS_execve 59
#define SYS_exit 60
#define SYS_kill 62
#define SYS_fcntl 72
#define SYS_chdir 80
#define SYS_mkdir 83
#define SYS_rmdir 84
#define SYS_creat 85
#define SYS_link 86
#define SYS_unlink 87
#define SYS_gettimeofday 96
#define SYS_time 201
#define SYS_openat 257
#define SYS_mkdirat 258
#elif defined(__aarch64__) || defined(__riscv)
#define SYS_getcwd 17
#define SYS_dup 23
#define SYS_fcntl 25
#define SYS_ioctl 29
#define SYS_mkdirat 34
#define SYS_unlinkat 35
#define SYS_openat 56
#define SYS_close 57
#define SYS_pipe2 59
#define SYS_lseek 62
#define SYS_read 63
#define SYS_write 64
#define SYS_fstat 80
#define SYS_exit 93
#define SYS_nanosleep 101
#define SYS_kill 129
#define SYS_rt_sigaction 134
#define SYS_gettimeofday 169
#define SYS_getpid 172
#define SYS_munmap 215
#define SYS_clone 220
#define SYS_execve 221
#define SYS_mmap 222
#elif defined(__i386__) || defined(__arm__) || defined(__powerpc__) ||         \
    defined(__POWERPC__)
#define SYS_exit 1
#define SYS_fork 2
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#define SYS_creat 8
#define SYS_link 9
#define SYS_unlink 10
#define SYS_execve 11
#define SYS_chdir 12
#ifndef __arm__
#define SYS_time 13
#endif
#define SYS_lseek 19
#define SYS_getpid 20
#define SYS_kill 37
#define SYS_mkdir 39
#define SYS_rmdir 40
#define SYS_pipe 42
#define SYS_ioctl 54
#define SYS_fcntl 55
#define SYS_gettimeofday 78
#define SYS_mmap 90
#define SYS_munmap 91
#define SYS_fstat 108
#define SYS_nanosleep 162
#if defined(__powerpc__) || defined(__POWERPC__)
#define SYS_rt_sigaction 173
#define SYS_getcwd 182
#else
#define SYS_rt_sigaction 174
#define SYS_getcwd 183
#endif
#if defined(__arm__)
#define SYS_openat 322
#define SYS_mkdirat 323
#elif defined(__powerpc__) || defined(__POWERPC__)
#define SYS_openat 286
#define SYS_mkdirat 287
#elif defined(__i386__)
#define SYS_openat 295
#define SYS_mkdirat 296
#endif
#else
#error architecture not supported
#endif

#endif
