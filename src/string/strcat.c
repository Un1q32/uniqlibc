char *strcat(char *restrict dst, const char *restrict src) {
  char *p = dst;
  while (*p)
    p++;
  while (*src)
    *p++ = *src++;
  *p = '\0';
  return dst;
}
