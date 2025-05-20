#ifndef _STDIO_H_
#define _STDIO_H_

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define L_ctermid PATH_MAX
#define L_tmpnam PATH_MAX

#define FILENAME_MAX PATH_MAX

#ifdef __UNIQLIBC_PRIVATE_API
typedef struct {
  char ungetcchar;       /* first character pushed back with ungetc */
  uint8_t flags;    /* flags to store things like buffer type */
  int fd;           /* file descriptor */
  char *writebuf;        /* write buffer */
  char *readbuf;       /* read buffer */
  char *ungetcbuf;       /* ungetc buffer */
  size_t writebufsize;   /* write buffer size */
  size_t writebufcount;  /* amount of bytes in write buffer */
  size_t readbufcount; /* amount of bytes in read buffer */
  size_t ungetcbufcount; /* amount of bytes in ungetc buffer */
  size_t listpos;   /* position in __open_stream_list */
  /* read, write, seek, and close functions to use */
  ssize_t (*read)(int, void *, size_t);
  ssize_t (*write)(int, const void *, size_t);
  off_t (*seek)(int, off_t, int);
  int (*close)(int);
} FILE;
#else
typedef struct {
  char __x;
} FILE;
#endif

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ 1024
#define EOF (-1)

#ifdef __APPLE__
#define P_tmpdir "/var/tmp"
#else
#define P_tmpdir "/tmp"
#endif

#define stdin stdin
#define stdout stdout
#define stderr stderr

#define getc(a) getc(a)

#ifdef __UNIQLIBC_PRIVATE_API
/* FILE stream flags */
#define __STDIO_LINEBUFFERED 0x01 /* stream is line buffered */
#define __STDIO_UNBUFFERED 0x02   /* stream is unbuffered */
#define __STDIO_EOF 0x04          /* stream has EOF flag set */
#define __STDIO_ERROR 0x08        /* stream has error flag set */
/* stream, write buffer, or read buffer were allocaed with malloc */
#define __STDIO_MALLOCED_STREAM 0x10
#define __STDIO_MALLOCED_WRITEBUF 0x20
#define __STDIO_MALLOCED_READBUF 0x40
#endif

__BEGIN_DECLS
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern int fputc(int, FILE *);
extern int putc(int, FILE *);
extern int putchar(int);
extern int puts(const char *);
extern int fputs(const char *, FILE *);
extern int printf(const char *, ...);
extern int fprintf(FILE *, const char *, ...);
extern int dprintf(int, const char *, ...);
extern int sprintf(char *, const char *, ...);
extern int snprintf(char *, size_t, const char *, ...);
extern int vprintf(const char *, va_list);
extern int vfprintf(FILE *, const char *, va_list);
extern int vdprintf(int, const char *, va_list);
extern int vsprintf(char *, const char *, va_list);
extern int vsnprintf(char *, size_t, const char *, va_list);
extern void perror(const char *);
extern FILE *fopen(const char *, const char *);
extern FILE *fdopen(int, const char *);
extern FILE *freopen(const char *, const char *, FILE *);
extern int fclose(FILE *);
extern void fcloseall(void);
extern int setvbuf(FILE *, char *, int, size_t);
extern int setlinebuf(FILE *);
extern void setbuffer(FILE *, char *, size_t);
extern void setbuf(FILE *, char *);
extern int fseek(FILE *, long, int);
extern void rewind(FILE *);
extern long ftell(FILE *);
extern int ferror(FILE *);
extern int fflush(FILE *);
extern int fpurge(FILE *);
extern int feof(FILE *);
extern void clearerr(FILE *);
extern ssize_t getline(char **, size_t *, FILE *);
extern ssize_t getdelim(char **, size_t *, int, FILE *);
extern int fgetc(FILE *);
extern int getc(FILE *);
extern int getchar(void);
extern int ungetc(int, FILE *);
extern char *fgets(char *, int, FILE *);
extern char *gets(char *);
extern size_t fread(void *, size_t, size_t, FILE *);
extern size_t fwrite(const void *, size_t, size_t, FILE *);
extern char *ctermid(char *);
extern int fileno(FILE *);
extern char *tmpnam(char *);

#ifdef __UNIQLIBC_PRIVATE_API
extern FILE **__open_stream_list;
extern int __fopen_mode_parse(const char *);
extern FILE *__fdopen(int, mode_t);
extern void __random_alnum(char *, size_t);
#endif
__END_DECLS

#endif
