#include <stdio.h>
#include <stdlib.h>

int __vsnprintf_chk(char *str, size_t maxlen, int flag, size_t slen,
                    const char *format, va_list ap) {
  (void)flag;

  if (maxlen > slen) {
    fputs("Buffer overflow detected!\n", stderr);
    abort();
  }

  return vsnprintf(str, maxlen, format, ap);
}
