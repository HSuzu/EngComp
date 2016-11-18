#ifndef LIST_H
#define LIST_H

#define TAM_PAL 9
#define TAM_SIG 101

typedef struct _no {
  char palavra[TAM_PAL];
  char significado[TAM_SIG];
  struct _no *prox;
} no;

typedef struct _list {
  no *inicio;
  int tam;
} List;

void criaList(List *list);
int addElemToList(List *list, char palavra[TAM_PAL], char significado[TAM_SIG]);
no *buscaList(List *list, char palavra[TAM_PAL]);
void destroiList(List *list);

#endif
