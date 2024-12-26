#include <stdio.h>

int main(void) {
  printf("num = %d\n", -123);
  printf("num2 = %d\n", 12345);
  printf("signed num2 = %+d\n", 12345);
  printf("num3 = %lld\n", 8589934592LL);
  printf("num4 = %llu\n", 0xFFFFFFFFFFFFFFFFULL);
  float num5 = 3.1415926535897932384;
  printf("num5 = %f\n", num5);
  printf("num5 percision 2 = %.2f\n", num5);
  printf("num5 percision 15 = %.15f\n", num5);
  printf("num5 percision 15 = %.*f\n", 15, num5);
  printf("num5 percision -15 = %.*f\n", -15, num5);
  printf("num5 percision 0 = %.0f\n", num5);
  printf("10 rounded = %f\n", 9.9999999);
  printf("-10 rounded = %f\n", -9.9999999);
  printf("32767 cast to unsigned char: %hhu\n", 32767);
  printf("percent sign: %%\n");
  printf("precise string: %.3s\n", "foobar");
  const char *str = "chars";
  printf("%c%c%c%c%c\n", str[0], str[1], str[2], str[3], str[4]);
  printf("1 with a width of 3 chars: %03d\n", 1);
  printf("signed -1 with a width of 3: %03d\n", -1);
  printf("negative zerofill: %0*dtest\n", -5, 1);
  printf("hex: %x\n", 0xdeadbeef);
  printf("HEX: %X\n", 0xdeadbeef);
  printf("hex alt: %#x\n", 0xdeadbeef);
  printf("small hex: %x\n", 0xabc);
  printf("small hex zero padded: %08x\n", 0xabc);
  printf("small hex zero padded alt: %#08x\n", 0xabc);
  printf("octal: %o\n", 01234567);
  printf("padded string:%10s\n", "hello");
  printf("dynamicly padded string:%*s\n", 10, "hello");
  printf("negative dynamicly padded string:%*sworld\n", -10, "hello");
  printf("pointer: %p\n", (void *)&num5);
  printf("wide string: %ls\n", L"hello");
  printf("binary: %b\n", 42);
  printf("binary alt: %#b\n", 42);
  printf("nan: %f\n", 0.0 / 0.0);
  printf("inf: %f\n", 1.0 / 0.0);
  printf("neginf: %f\n", -1.0 / 0.0);
  printf("uppercase nan: %F\n", 0.0 / 0.0);
  printf("bigfloat: %.0Lf\n", 314159265358979323846.2L);
  int charcount = 0;
  printf("Hello, %s!\n%n", "World", &charcount);
  if (charcount != 14)
    printf("Incorrect charcount, expected 14 got %d\n", charcount);
  else
    printf("Correct charcount, expected 14 got %d\n", charcount);

  return 0;
}
