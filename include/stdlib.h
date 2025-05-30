#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <alloca.h>
#include <malloc.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __UNIQLIBC_PRIVATE_API
#include <stdbool.h>
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define RAND_MAX 0x7FFFFFFF

__BEGIN_DECLS
extern void exit(int);
extern void _Exit(int);
extern long strtol(const char *, char **, int);
extern long long strtoll(const char *, char **, int);
extern quad_t strtoq(const char *, char **, int);
extern unsigned long strtoul(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern u_quad_t strtouq(const char *, char **, int);
extern int atoi(const char *);
extern long atol(const char *);
extern long long atoll(const char *);
extern double atof(const char *);
extern char *getenv(const char *);
extern int setenv(const char *, const char *, int);
extern int putenv(char *);
extern int unsetenv(const char *);
extern int clearenv(void);
extern int system(const char *);
extern void srand(unsigned int);
extern int rand(void);
extern int atexit(void (*)(void));
extern long double strtold(const char *, char **);
extern double strtod(const char *, char **);
extern float strtof(const char *, char **);
extern int abs(int);
extern void abort(void);
extern uint32_t arc4random(void);
extern void arc4random_buf(void *, size_t);

#ifdef __UNIQLIBC_PRIVATE_API
extern int __rand(unsigned int);
extern ssize_t __findenv(const char *);
extern int __putenv(char *, ssize_t, bool);
extern bool *__envshouldfree;
extern unsigned int __random_seed;
extern void (*__atexit_funcs[32])(void);
extern void (**__atexit_funcs_extra)(void);
extern size_t __atexit_count;
#ifdef __MACH__
extern void __stack_protect_init(char **);
#else
extern void __stack_protect_init(void);
#endif
#endif
__END_DECLS

#endif
