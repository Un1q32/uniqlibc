#include <stdio.h>
#include <string.h>

int main(void) {
  ungetc('c', stdin);
  ungetc('b', stdin);
  ungetc('a', stdin);
  fputs("input: ", stdout);
  fflush(stdout);
  char c[4];
  fread(c, 1, 4, stdin);
  if (memcmp(c, "abc", 3) == 0)
    printf("output: %c\n", c[3]);
  else
    puts("ungetc failed");
  return 0;
}
