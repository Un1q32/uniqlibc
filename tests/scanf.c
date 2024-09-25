#include <stdio.h>

int main(void) {
  int a = 0, b = 0;
  long long c = 0;
  unsigned int d = 0;
  char str[14];
  char *nothing = NULL;
  wchar_t wstr[11];
  int ret = sscanf("123%456 987 notwhitespacex8589934592 54321 longstring",
                   "%d%%%d %*d %13sx%lld %u %ls%s", &a, &b, str, &c, &d, wstr,
                   nothing);
  printf("a = %d, b = %d\n", a, b);
  printf("c = %lld\n", c);
  printf("d = %u\n", d);
  printf("str = %s\n", str);
  printf("wstr = %ls\n", wstr);
  if (ret == 6) {
    puts("All conversions successful");
    return 0;
  } else {
    puts("Some conversions failed");
    return 1;
  }
}
