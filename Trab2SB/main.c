#include "compilalinb.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  unsigned char codigo[1000];
  FILE *arq = fopen("nome.txt", "r");
  funcp f = compilaLinB(arq, codigo);/*
   for (int i = 0; i < 100; i++) {
       printf("%d -- %0x\n", i, codigo[i]);
   }*/
  int i = (*f)(4);
  printf("%d\n", i);
  fclose(arq);
  return 0;
}
