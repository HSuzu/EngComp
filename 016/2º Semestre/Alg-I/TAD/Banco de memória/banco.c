#include "banco.h"

void cria(Banco *b) {
  b->inicio = -1;
  b->fim = -1;

  int i;
  for(i = 0; i < TAM-1; i++)
    b->itens[i].prox = i+1;
  b->itens[TAM-1].prox = -1

  b->vazio = 0;
}

void getNode(Banco *b, int *no) {
  if(b->vazio >= 0) {
    *no = b->vazio;
    b->itens[*no].prox = -1;
    b->vazio = b->itens[b->vazio].prox;
  } else
    *no = -1;
}

void freeNode(Banco *b, int *no) {
  b->itens[*no].prox = b->vazio;
  b->vazio = no;
}

int isEmpty()
