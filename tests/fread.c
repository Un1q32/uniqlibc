#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  unsigned char color = 0;
  char colorstr[13];
  strcpy(colorstr, "\033[38;5;000mC");
  int c;
  while ((c = fgetc(file)) != EOF) {
    colorstr[9] = color % 10 + '0';
    colorstr[8] = (color / 10) % 10 + '0';
    colorstr[7] = (color / 100) % 10 + '0';
    colorstr[11] = c;
    fputs(colorstr, stdout);
    color = (color + 1) % 256;
  }

  fclose(file);
  return 0;
}
