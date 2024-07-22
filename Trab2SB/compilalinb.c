/* TURMAS DIFERENTES!!!*/
/* Gabriel Augusto Gedey Porto 2210508 3WB */
/* João Gabriel da Cunha Vasconcellos Matricula 2211302 3WC */

#include "compilalinb.h"
#include <stdio.h>
#include <stdlib.h>

typedef int (*funcp)();

typedef union num { // union para escrever o inteiro bit a bit
  int integer;
  unsigned char byte[4];
} Num;

struct elTabela { // elemento da tabela para o if
  unsigned char *p1;
  unsigned char *p2;
  unsigned char *p3;
  unsigned char *p4;
  int lInicial;
  int lFinal;
  struct elTabela *proximo; 
};
typedef struct elTabela ElTabela;

typedef struct tabela { //tabela para o if
  ElTabela *inicio;
  int tam;
} Tabela;

static void error(const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

funcp compilaLinB(FILE *f, unsigned char codigo[]) {
  unsigned char *pos = codigo;
  int tamLinha[50];
  int nLinha = 0;

  Tabela tabela;
  tabela.tam = 0;
  tabela.inicio = NULL;
  int ret = 0;
  char c;
  *pos++ = 0x55; // pusq %rbp
  *pos++ = 0x48; // movq %rbp, %rsp
  *pos++ = 0x89;
  *pos++ = 0xe5; //

  *pos++ = 0x48; // subq $16, %rsp
  *pos++ = 0x83;
  *pos++ = 0xec;
  *pos++ = 0x10; //
  if (fscanf(f, " ") != 0) {
      error("comando invalido", nLinha + 1);
    }
  while ((c = fgetc(f)) != EOF) {
    tamLinha[nLinha] = 0;
    if (c == 'v') {
      int idx0, idx1, idx2;
      char var1, var2, op;
      if (fscanf(f, "%d <= %c%d %c %c%d", &idx0, &var1, &idx1, &op, &var2,
                 &idx2) != 6) {
        error("comando invalido", nLinha + 1);
      }

      if (var1 == 'p') {
        *pos++ = 0x41; // movl %edi|%esi, %r10d
        *pos++ = 0x89;
        *pos++ = 0xfa - ((idx1 - 1) * 8); //
        tamLinha[nLinha] += 3;
      } else if (var1 == 'v') {
        *pos++ = 0x44; // movl -n(%rbp), %r10d
        *pos++ = 0x8b;
        *pos++ = 0x55;
        *pos++ = 0xfc - (idx1 - 1) * 4; //
        tamLinha[nLinha] += 4;
      } else {
        *pos++ = 0x41; //movl $n, %r10d
        *pos++ = 0xba;
        Num num;
        num.integer = idx1;
        *pos++ = num.byte[0];
        *pos++ = num.byte[1];
        *pos++ = num.byte[2];
        *pos++ = num.byte[3]; //
        tamLinha[nLinha] += 6;
      }
      if (op == '+') {
        if (var2 == 'p') {
          *pos++ = 0x41; // addl %edi|%esi, %r10d
          *pos++ = 0x01;
          *pos++ = 0xfa - (idx2 - 1) * 8; //
          tamLinha[nLinha] += 3;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // addl -n(%rbp), %r10d
          *pos++ = 0x03;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4; //
          tamLinha[nLinha] += 4;
        } else {
          *pos++ = 0x41; //addl $n, %r10d 
          *pos++ = 0x81;
          *pos++ = 0xc2;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3];//
          tamLinha[nLinha] += 7; 
        }
      } else if (op == '-') {
        if (var2 == 'p') {
          *pos++ = 0x41; // subl %edi|%esi, %r10d
          *pos++ = 0x29;
          *pos++ = 0xfa - (idx2 - 1) * 8; //
          tamLinha[nLinha] += 3;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // subl -n(%rbp), %r10d
          *pos++ = 0x2b;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4; //
          tamLinha[nLinha] += 4;
        } else {
          *pos++ = 0x41; //subl $n, %r10d 
          *pos++ = 0x81;
          *pos++ = 0xea;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3]; //
          tamLinha[nLinha] += 7;
        }
      } else {
        if (var2 == 'p') {
          *pos++ = 0x44; // imull %edi|%esi, %r10d
          *pos++ = 0x0f;
          *pos++ = 0xaf;
          *pos++ = 0xd7 - (idx2 - 1); //
          tamLinha[nLinha] += 4;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // imull %-n(%rbp), %r10d
          *pos++ = 0x0f;
          *pos++ = 0xaf;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4; //
          tamLinha[nLinha] += 5;
        } else {
          *pos++ = 0x45; //imull $n, %r10d 
          *pos++ = 0x69;
          *pos++ = 0xd2;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3]; 
          tamLinha[nLinha] += 7;
        }
      }
      *pos++ = 0x44;
      *pos++ = 0x89;
      *pos++ = 0x55;
      *pos++ = 0xfc - (idx0 - 1) * 4; //
      tamLinha[nLinha] += 4;
    } else if (c == 'p') {
      int idx0, idx1, idx2;
      char var1, var2, op;
      if (fscanf(f, "%d <= %c%d %c %c%d", &idx0, &var1, &idx1, &op, &var2,
                 &idx2) != 6) {
        error("comando invalido", nLinha + 1);
      }

      if (var1 == 'p') {
        *pos++ = 0x41; // movl %edi|%esi, %r10d
        *pos++ = 0x89;
        *pos++ = 0xfa - ((idx1 - 1) * 8); //
        tamLinha[nLinha] += 3;
      } else if (var1 == 'v') {
        *pos++ = 0x44; // movl -n(%rbp), %r10d
        *pos++ = 0x8b;
        *pos++ = 0x55;
        *pos++ = 0xfc - (idx1 - 1) * 48; //
        tamLinha[nLinha] += 4;
      } else {
        *pos++ = 0x41;  //movl $n, %r10d
        *pos++ = 0xba;
        Num num;
        num.integer = idx1;
        *pos++ = num.byte[0];
        *pos++ = num.byte[1];
        *pos++ = num.byte[2];
        *pos++ = num.byte[3];
        tamLinha[nLinha] += 6; //
      }
      if (op == '+') {
        if (var2 == 'p') {
          *pos++ = 0x41; // addl %edi|%esi, %r10d
          *pos++ = 0x01;
          *pos++ = 0xfa - (idx2 - 1) * 8; //
          tamLinha[nLinha] += 3;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // addl -n(%rbp), %r10d
          *pos++ = 0x03;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4; //
          tamLinha[nLinha] += 4;
        } else {
          *pos++ = 0x41; //addl $n, %r10d
          *pos++ = 0x81;
          *pos++ = 0xc2;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3];
          tamLinha[nLinha] += 7; //
        }
      } else if (op == '-') {
        if (var2 == 'p') {
          *pos++ = 0x41; // subl %edi|%esi, %r10d
          *pos++ = 0x29;
          *pos++ = 0xfa - (idx2 - 1) * 8; //
          tamLinha[nLinha] += 3;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // subl -n(%rbp), %r10d
          *pos++ = 0x2b;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4; //
          tamLinha[nLinha] += 4;
        } else {
          *pos++ = 0x41; //subl $n, %r10d
          *pos++ = 0x81;
          *pos++ = 0xea;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3];
          tamLinha[nLinha] += 7; //
        }
      } else {
        if (var2 == 'p') {
          *pos++ = 0x44; // imull %edi|%esi, %r10d
          *pos++ = 0x0f;
          *pos++ = 0xaf;
          *pos++ = 0xd7 - (idx2 - 1);
          tamLinha[nLinha] += 4;
        } else if (var2 == 'v') {
          *pos++ = 0x44; // imull %edi|%esi, %r10d
          *pos++ = 0x0f;
          *pos++ = 0xaf;
          *pos++ = 0x55;
          *pos++ = 0xfc - (idx2 - 1) * 4;
          tamLinha[nLinha] += 5;
        } else {
          *pos++ = 0x45; //imull $n, %r10d
          *pos++ = 0x69;
          *pos++ = 0xd2;
          Num num;
          num.integer = idx2;
          *pos++ = num.byte[0];
          *pos++ = num.byte[1];
          *pos++ = num.byte[2];
          *pos++ = num.byte[3];
          tamLinha[nLinha] += 7;
        }
      }
      *pos++ = 0x44;
      *pos++ = 0x89;
      *pos++ = 0xd8 - (idx0); //
      tamLinha[nLinha] += 3;
    } else if (c == 'i') {
      char var0;
      int idx0, num;
      if (fscanf(f, "f %c%d %d", &var0, &idx0, &num) != 3) {
        error("comando invalido", nLinha + 1);
      }
      if (var0 == 'v') {
        *pos++ = 0x83; //cmpl -n(%rbp), $0
        *pos++ = 0x7d;
        *pos++ = 0xfc - (idx0 - 1) * 4;
        tamLinha[nLinha] += 3;
      } else {
        *pos++ = 0x83; // cmpl %edi|%esi, $0
        *pos++ = 0xff + 1 - (int)(idx0);
        tamLinha[nLinha] += 2;
      }
      *pos++ = 0x00; //
      *pos++ = 0x0f; // jne
      *pos++ = 0x85;

      ElTabela *elemento = (ElTabela *)(malloc(sizeof(ElTabela))); //cria um elemento pra colocar na tabela
      elemento->lInicial = nLinha + 1; // linha onde vc está



      elemento->p1 = pos++; //abrindo espaço e guardando em ponteiros
      elemento->p2 = pos++;
      elemento->p3 = pos++;
      elemento->p4 = pos++; //

      int line = num;
      elemento->lFinal = line; // linha para onde vc vai pular
      
      elemento->proximo = tabela.inicio; //insere na tabela
      tabela.inicio = elemento; //
      tabela.tam += 1;
      
      
      tamLinha[nLinha] += 7;
    } else if (c == 'r') {
      if (fscanf(f, "et") != 0) {
        error("comando invalido", nLinha + 1);
      }
      *pos++ = 0x8b; // movl -4(%rbp), %eax
      *pos++ = 0x45;
      *pos++ = 0xfc; //

      *pos++ = 0xc9; // leave
      *pos++ = 0xc3; // ret
      ret = 1;
      tamLinha[nLinha] += 5;
    } else {
      error("comando desconhecido", nLinha + 1);
    }
    nLinha++;
    if (fscanf(f, " ") != 0) {
      error("comando invalido", nLinha + 1);
    }
  }
  ElTabela *el = tabela.inicio; //percorre a tabela calculando as distancias 
  for (int j = 0; j < tabela.tam; j++) {
    Num dist;
    dist.integer = 0;
    if (el->lFinal > el->lInicial) {
      if (nLinha < el->lFinal) {
        error("jump para linha inexistente", el->lFinal);
      }
      for (int k = el->lInicial; k < (el->lFinal - 1); k++) {
        dist.integer += tamLinha[k];
      }
    } else {
      for (int k = (el->lFinal - 1); k < el->lInicial; k++) {
        dist.integer -= tamLinha[k];
      }
    }//
    *(el->p1) = dist.byte[0]; // coloca a distancia na area aberta na memoria
    *(el->p2) = dist.byte[1];
    *(el->p3) = dist.byte[2];
    *(el->p4) = dist.byte[3]; //
    el = el->proximo;
  }
  if (ret == 0) { // se chegar no final do arquivo sem ret
    *pos++ = 0x8b; // movl -4(%rbp), %eax
    *pos++ = 0x45;
    *pos++ = 0xfc; //
    *pos++ = 0xc9; // leave
    *pos++ = 0xc3; // ret
  }
  return (funcp)codigo;
}