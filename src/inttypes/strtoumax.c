#include <inttypes.h>

uintmax_t strtoumax(const char *nptr, char **endptr, int base) {
  return strtoimax(nptr, endptr, base);
}
