#include <stdlib.h>

float strtof(const char *nptr, char **endptr) { return strtold(nptr, endptr); }
