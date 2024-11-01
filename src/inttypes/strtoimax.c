#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>

intmax_t strtoimax(const char *nptr, char **endptr, int base) {
  while (isspace(*nptr))
    ++nptr;

  bool negative = false;
  if (nptr[0] == '-') {
    negative = true;
    ++nptr;
  } else if (nptr[0] == '+')
    ++nptr;

  if (base == 0) {
    if (nptr[0] == '0') {
      if (nptr[1] == 'x' || nptr[1] == 'X') {
        base = 16;
        nptr += 2;
      } else if (nptr[1] == 'b' || nptr[1] == 'B') {
        base = 2;
        nptr += 2;
      } else {
        base = 8;
        nptr += 1;
      }
    } else
      base = 10;
  } else if (base == 16) {
    if (nptr[0] == '0' && (nptr[1] == 'x' || nptr[1] == 'X'))
      nptr += 2;
  } else if (base == 2) {
    if (nptr[0] == '0' && (nptr[1] == 'b' || nptr[1] == 'B'))
      nptr += 2;
  }

  intmax_t num = 0;

  while (1) {
    char digit;
    if (*nptr >= '0' && *nptr <= '9')
      digit = *nptr - '0';
    else if (*nptr >= 'a' && *nptr <= 'z')
      digit = *nptr - 'a' + 10;
    else if (*nptr >= 'A' && *nptr <= 'Z')
      digit = *nptr - 'A' + 10;
    else
      break;
    if (digit >= base)
      break;

    num = num * base + digit;
    ++nptr;
  }

  if (negative)
    num = -num;
  if (endptr)
    *endptr = (char *)nptr;
  return num;
}
