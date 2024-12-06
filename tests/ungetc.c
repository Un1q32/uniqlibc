#include <stdio.h>
#include <string.h>

int main(void) {
  ungetc('c', stdin);
  ungetc('b', stdin);
  ungetc('a', stdin);
  fputs("input: ", stdout);
  fflush(stdout);
  char c[5];
  fread(c, 1, 4, stdin);
  c[4] = '\0';
  if (memcmp(c, "abc", 3) == 0)
    printf("output: %c\n", c[3]);
  else {
    puts("ungetc failed");
    printf("expected: abc%c\n", c[3]);
    printf("got: %s\n", c);
  }
  return 0;
}
