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
              if((*r)->dir->fb != 0) // a subarvore da subarvore da direita está tendendo para a direita
                ((*r)->fb)++;
              *c = 1; // e a arvore cresce....
              break;
          }
        }
      }
    } else {
      if( (returnValue = r_inserir(&((*r)->esq), x, c)) == 0 ) { // inseriu a esquerda
        if(*c) {
          switch ((*r)->fb) {
            case -1: // tendendo a esq
              if((*r)->esq->fb != 0) // sub.a da sub.a tendendo a esq
                ((*r)->fb)--;
              *c = 1;
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

int isAVL(no *raiz) {
  if(!raiz) // raiz == NULL
    return 1;

  if(raiz->fb > 1 || raiz->fb < -1)
    return 0;


  if(isAVL(raiz->dir)) {
    if(isAVL(raiz->esq))
      return 1;

    return 0;
  }

  return 0;
}
