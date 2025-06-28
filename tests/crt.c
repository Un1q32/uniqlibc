#include <stdio.h>

int main(int argc, const char *argv[], const char *envp[]) {
  printf("argc: %d\n", argc);
  int i;
  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
  for (i = 0; envp[i] != NULL; i++)
    printf("envp[%d]: %s\n", i, envp[i]);
  return 0;
}
