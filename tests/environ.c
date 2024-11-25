#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const char *str = "TESTENV=teststr";
  size_t len = strlen(str);
  char envstr[len + 1];

  memcpy(envstr, str, len);
  envstr[len] = '\0';
  putenv(envstr);

  puts(getenv("TESTENV"));
  memcpy(envstr + len - 3, "val", 3);
  puts(getenv("TESTENV"));
  setenv("TESTENV", "teststring", 1);
  putenv(envstr);
  puts(getenv("TESTENV"));
  setenv("TESTENV", "strtest", 1);
  puts(getenv("TESTENV"));

  return 0;
}
