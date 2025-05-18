#ifndef _SYS_LINUX_SYSCALL_H_
#define _SYS_LINUX_SYSCALL_H_

#if defined(__x86_64__)
#define SYS_read 0
#define SYS_write 1
#define SYS_open 2
#define SYS_close 3
#define SYS_lseek 8
#define SYS_mmap 9
#define SYS_munmap 11
#define SYS_ioctl 16
#define SYS_access 21
#define SYS_pipe 22
#define SYS_dup 32
#define SYS_dup2 33
#define SYS_getpid 39
#define SYS_fork 57
#define SYS_vfork 58
#define SYS_execve 59
#define SYS_exit 60
#define SYS_wait4 61
#define SYS_kill 62
#define SYS_fcntl 72
#define SYS_getcwd 79
#define SYS_chdir 80
#define SYS_fchdir 81
#define SYS_mkdir 83
#define SYS_rmdir 84
#define SYS_creat 85
#define SYS_link 86
#define SYS_unlink 87
#define SYS_gettimeofday 96
#define SYS_getuid 102
#define SYS_getgid 104
#define SYS_setuid 105
#define SYS_setgid 106
#define SYS_geteuid 107
#define SYS_getegid 108
#define SYS_getsid 124
#define SYS_time 201
#define SYS_openat 257
#define SYS_mkdirat 258
#define SYS_faccessat 269
#elif defined(__aarch64__) || defined(__riscv)
#define SYS_getcwd 17
#define SYS_dup 23
#define SYS_fcntl 25
#define SYS_ioctl 29
#define SYS_mkdirat 34
#define SYS_unlinkat 35
#define SYS_faccessat 48
#define SYS_chdir 49
#define SYS_openat 56
#define SYS_close 57
#define SYS_pipe2 59
#define SYS_lseek 62
#define SYS_read 63
#define SYS_write 64
#define SYS_exit 93
#define SYS_kill 129
#define SYS_setgid 144
#define SYS_setuid 146
#define SYS_getsid 156
#define SYS_gettimeofday 169
#define SYS_getpid 172
#define SYS_getuid 174
#define SYS_geteuid 175
#define SYS_getgid 176
#define SYS_getegid 177
#define SYS_munmap 215
#define SYS_clone 220
#define SYS_execve 221
#define SYS_mmap 222
#define SYS_wait4 260
#elif defined(__i386__) || defined(__arm__) || defined(__powerpc__) ||         \
    defined(__POWERPC__)
#define SYS_exit 1
#define SYS_fork 2
#define SYS_read 3
#define SYS_write 4
#define SYS_open 5
#define SYS_close 6
#ifndef __arm__
#define SYS_waitpid 7
#endif
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
#define SYS_setuid 23
#define SYS_getuid 24
#define SYS_access 33
#define SYS_kill 37
#define SYS_mkdir 39
#define SYS_rmdir 40
#define SYS_pipe 42
#define SYS_setgid 46
#define SYS_getgid 47
#define SYS_seteuid 49
#define SYS_setegid 50
#define SYS_ioctl 54
#define SYS_fcntl 55
#define SYS_gettimeofday 78
#define SYS_mmap 90
#define SYS_munmap 91
#define SYS_wait4 114
#define SYS_vfork 190
#define SYS_getsid 147
#define SYS_faccessat 307
#if defined(__powerpc__) || defined(__POWERPC__)
#define SYS_getcwd 182
#else
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
