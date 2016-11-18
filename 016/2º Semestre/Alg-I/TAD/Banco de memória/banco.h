#ifndef __BANCO
#define __BANCO

#define TAM 250

typedef char elem

typedef struct _no {
  elem info;
  int prox;
} no;

typedef struct _banco {
  int inicio, fim;
  int vazio;
  no itens[TAM];
}

#endif
