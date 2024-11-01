#include <inttypes.h>

intmax_t strtoimax(const char *nptr, char **endptr, int base) {
  if (nptr[0] == '-') {
    uintmax_t ret = strtoumax(nptr + 1, endptr, base);
    return -ret;
  } else
    return strtoumax(nptr, endptr, base);
}
