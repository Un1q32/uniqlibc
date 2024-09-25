#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int ret = write(STDOUT_FILENO, "Hello, world!\n", 14);
  if (ret != 14)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
