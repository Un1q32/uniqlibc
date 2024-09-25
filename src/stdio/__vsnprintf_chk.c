#include <stdio.h>

int __vsnprintf_chk(char *str, size_t maxlen, int flag, size_t slen,
                    const char *format, va_list ap) {
  (void)flag;
  (void)slen;
  return vsnprintf(str, maxlen, format, ap);
}
