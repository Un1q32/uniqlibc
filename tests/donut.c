#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#define R(t, x, y)                                                             \
  f = x;                                                                       \
  x -= t * y;                                                                  \
  y += t * f;                                                                  \
  f = (3 - x * x - y * y) / 2;                                                 \
  x *= f;                                                                      \
  y *= f;

int i, j, k, x, y, o, N;

static char *utoa(unsigned int num, char *buf) {
  char *p = buf + 10;
  *p = '\0';
  do {
    *--p = '0' + (num % 10);
    num /= 10;
  } while (num);
  return p;
}

int main(void) {
  const char *resetstr = "\x1b[23AFPS: ";
  size_t resetstrlen = strlen(resetstr);
  float z[1760], a = 0, e = 1, c = 1, d = 0, f, g, h, G, H, A, t, D;
  char b[1761 + resetstrlen + 11];
  unsigned int thisfps = 0, fps = 0;
  time_t currentsec = 0, oldsec = 0;
  memcpy(b + 1761, resetstr, resetstrlen);
  for (;;) {
    memset(b, ' ', 1760);
    g = 0, h = 1;
    bzero(z, sizeof(z));
    for (j = 0; j < 90; j++) {
      G = 0, H = 1;
      for (i = 0; i < 314; i++) {
        A = h + 2, D = 1 / (G * A * a + g * e + 5);
        t = G * A * e - g * a;
        x = 40 + 30 * D * (H * A * d - t * c);
        y = 12 + 15 * D * (H * A * c + t * d);
        o = x + 80 * y;
        N = 8 * ((g * a - G * h * e) * d - G * h * a - g * e - H * h * c);
        if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
          z[o] = D;
          b[o] = (N > 0 ? N : 0)[".,-~:;=!*#$@"];
        }
        R(.02, H, G);
      }
      R(.07, h, g);
    }
    for (k = 0; 1761 > k; k += 80)
      b[k] = '\n';
    char fpsbuf[11];
    char *bufp = stpcpy(b + 1761 + resetstrlen, utoa(fps, fpsbuf));
    write(STDOUT_FILENO, b, bufp - b);
    currentsec = time(NULL);
    if (currentsec > oldsec) {
      oldsec = currentsec;
      fps = thisfps;
      thisfps = 0;
    } else
      ++thisfps;
    R(.04, e, a);
    R(.02, d, c);
  }
}
