/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/
#include "avl.h"
#include<stdio.h>
#include<stdlib.h>

void cria(AVL *a) {
  a->raiz = NULL;
}

void delete(no *a) { // remover arvore
  if(!a)
    return;

  delete(a->dir);
  delete(a->esq);

  free(a);
}

void rEE(no **n) {
  no *pai = *n;
  no *filho = pai->esq;

  *n = filho;
  pai->esq = filho->dir;
  filho->dir = pai;

  pai->fb = 0;
  filho->fb = 0;
}

void rDD(no **n) {
  no *pai = *n;
  no *filho = pai->dir;

  *n = filho;
  pai->dir = filho->esq;
  filho->esq = pai;

  pai->fb = 0;
  filho->fb = 0;
}

void rED(no **n) {
  no *pai   = *n;
  no *filho = pai->esq;
  no *neto  = filho->dir;

  filho->dir = neto->esq;
  pai->esq   = neto->dir;
  neto->esq  = filho;
  neto->dir  = pai;

  switch(neto->fb) {
    case -1:
      pai->fb = 1;
      filho->fb = 0;
      break;
    case 0:
      pai->fb = 0;
      filho->fb = 0;
      break;
    case 1:
      pai->fb = 0;
      filho->fb = -1;
      break;
    default:
      fprintf(stderr, "-1\n");
      break;
  }

  *n = neto;
  neto->fb = 0;
}

void rDE(no **n) {
  no *pai   = *n;
  no *filho = pai->dir;
  no *neto  = filho->esq;

  filho->esq = neto->dir;
  pai->dir   = neto->esq;
  neto->dir  = filho;
  neto->esq  = pai;

  switch(neto->fb) {
    case -1:
      pai->fb = 1;
      filho->fb = 0;
      break;
    case 0:
      pai->fb = 0;
      filho->fb = 0;
      break;
    case 1:
      pai->fb = 0;
      filho->fb = -1;
      break;
    default:
      fprintf(stderr, "-1\n");
      break;
  }

  *n = neto;
  neto->fb = 0;
}

int r_inserir(no **r, elem *x, int *c) {
  if(!(*r)) {
    *r = (no *)malloc(sizeof(no));
    if(*r == NULL)
      return -1; // erro ao add

    (*r)->dir = NULL;
    (*r)->esq = NULL;
    (*r)->fb = 0;
    (*r)->info = *x;

    *c = 1;

    return 0; // sucesso ao add
  }

  if(*x == (*r)->info)
    return 1; // elemento já existe


  int returnValue = 0;
  if(*x > (*r)->info) {
    if( (returnValue = r_inserir(&((*r)->dir), x, c)) == 0 ) { // insere na direita
      if(*c) { // a arvore cresceu
        switch ((*r)->fb) {
          case -1: // se a arvore estava tendendo para a esquerda
            (*r)->fb = 0; // o tamanho da direita e esquerda são iguais
            *c = 0; // a inserção do elemento não aumentou o tamanho da arvore
            break;
          case 0: // as subarvores tinham a mesma altura
            (*r)->fb = 1; // então a subarvore da dir ficou maior do q a esq
            *c = 1; // portanto, a arvore cresceu
            break;
          case 1: // a subarvore da direita era maior do q a da esq
            if((*r)->dir->fb == 1) // a subarvore da subarvore da direita está tendendo para a direita
              rDD(r); // logo, rotacionamos com DD
            else // a sub.a da sub.a não está tend. a dir. (caso fb = 0, teremos q tratar com DE - DD não suporta -) --------------------------------------
              rDE(r); // logo, rotacionamos com DE
            *c = 0; // e a arvore não cresce....
            break;
        }
      }
    }
  } else {
    if( (returnValue = r_inserir(&((*r)->esq), x, c)) == 0 ) { // inseriu a esquerda
      if(*c) {
        switch ((*r)->fb) {
          case -1: // tendendo a esq
            if((*r)->esq->fb == -1) // sub.a da sub.a tendendo a esq
              rEE(r);
            else
              rED(r);
            *c = 0;
            break;
          case 0:
            (*r)->fb = -1;
            *c = 1;
            break;
          case 1:
            (*r)->fb = 0;
            *c = 0;
            break;
        }
      }
    }
  }

  return returnValue;
}

int inserir(AVL *a, elem *x) {
  int c;
  return r_inserir(&(a->raiz), x, &c);
}

elem r_pai(no *raiz, elem *child) {
  if(!(raiz->dir)) // pai não encontrado
    return -1;

  if(*child > raiz->info) {
    if(*child == raiz->dir->info)
      return raiz->info;

    return r_pai(raiz->dir, child);
  }

  // child->info < raiz->info
  if(!(raiz->esq))
    return -1;

  if(*child == raiz->esq->info)
    return raiz->info;

  return r_pai(raiz->esq, child);
}

elem pai(AVL *a, elem *child) {
  if(a->raiz->info == *child) // child == raiz
    return -1;

  return r_pai(a->raiz, child);
}
