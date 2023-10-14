#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  signed char sc = -1;
  unsigned int ui = sc;
  printf("sc=%d, ui=%u \n", sc, ui);
  printf("dump de sc: \n");
  dump(&sc, sizeof(sc));
  printf("dump de ui: \n");
  dump(&ui, sizeof(ui));
  return 0;
}
