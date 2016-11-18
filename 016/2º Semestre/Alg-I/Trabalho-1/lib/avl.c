/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/

#include "avl.h"
#include<stdio.h>
#include<stdlib.h>

void create(AVL *a) {
  a->root = NULL;
  a->numElem = 0;
}

void delete(NodeAVL *a) { // remover arvore
  if(!a)
    return;

  delete(a->right);
  delete(a->left);

  free(a);
}

void LLr(NodeAVL **n) {
  NodeAVL *father = *n;
  NodeAVL *son = father->left;

  *n = son;
  father->left = son->right;
  son->right = father;

  father->bf = 0;
  son->bf = 0;
}

void RRr(NodeAVL **n) {
  NodeAVL *father = *n;
  NodeAVL *son = father->right;

  *n = son;
  father->right = son->left;
  son->left = father;

  father->bf = 0;
  son->bf = 0;
}

void LRr(NodeAVL **n) {
  NodeAVL *father   = *n;
  NodeAVL *son = father->left;
  NodeAVL *grandson  = son->right;

  son->right = grandson->left;
  father->left   = grandson->right;
  grandson->left  = son;
  grandson->right  = father;

  switch(grandson->bf) {
    case -1:
      father->bf = 1;
      son->bf = 0;
      break;
    case 0:
      father->bf = 0;
      son->bf = 0;
      break;
    case 1:
      father->bf = 0;
      son->bf = -1;
      break;
    default:
      fprintf(stderr, "-1\n");
      break;
  }

  *n = grandson;
  grandson->bf = 0;
}

void RLr(NodeAVL **n) {
  NodeAVL *father   = *n;
  NodeAVL *son = father->right;
  NodeAVL *grandson  = son->left;

  son->left = grandson->right;
  father->right   = grandson->left;
  grandson->right  = son;
  grandson->left  = father;

  switch(grandson->bf) {
    case -1:
      father->bf = 1;
      son->bf = 0;
      break;
    case 0:
      father->bf = 0;
      son->bf = 0;
      break;
    case 1:
      father->bf = 0;
      son->bf = -1;
      break;
    default:
      fprintf(stderr, "-1\n");
      break;
  }

  *n = grandson;
  grandson->bf = 0;
}

int r_insert(NodeAVL **r, elem *x, int *c) {
  if(!(*r)) {
    *r = (NodeAVL *)malloc(sizeof(NodeAVL));
    if(*r == NULL)
      return -1; // erro ao add

    (*r)->right = NULL;
    (*r)->left = NULL;
    (*r)->bf = 0;
    (*r)->info = *x;

    *c = 1;

    return 0; // sucesso ao add
  }

  if(*x == (*r)->info)
    return 1; // elemento já existe


  int returnValue = 0;
  if(*x > (*r)->info) {
    if( (returnValue = r_insert(&((*r)->right), x, c)) == 0 ) { // insere na direita
      if(*c) { // a arvore cresceu
        switch ((*r)->bf) {
          case -1: // se a arvore estava tendendo para a esquerda
            (*r)->bf = 0; // o tamanho da direita e esquerda são iguais
            *c = 0; // a inserção do elemento não aumentou o tamanho da arvore
            break;
          case 0: // as subarvores tinham a mesma altura
            (*r)->bf = 1; // então a subarvore da dir ficou maior do q a esq
            *c = 1; // portanto, a arvore cresceu
            break;
          case 1: // a subarvore da direita era maior do q a da esq
            if((*r)->right->bf == 1) // a subarvore da subarvore da direita está tendendo para a direita
              RRr(r); // logo, rotacionamos com DD
            else // a sub.a da sub.a não está tend. a dir. (caso fb = 0, teremos q tratar com DE - DD não suporta -) --------------------------------------
              RLr(r); // logo, rotacionamos com DE
            *c = 0; // e a arvore não cresce....
            break;
        }
      }
    }
  } else {
    if( (returnValue = r_insert(&((*r)->left), x, c)) == 0 ) { // inseriu a esquerda
      if(*c) {
        switch ((*r)->bf) {
          case -1: // tendendo a esq
            if((*r)->left->bf == -1) // sub.a da sub.a tendendo a esq
              LLr(r);
            else
              LRr(r);
            *c = 0;
            break;
          case 0:
            (*r)->bf = -1;
            *c = 1;
            break;
          case 1:
            (*r)->bf = 0;
            *c = 0;
            break;
        }
      }
    }
  }

  return returnValue;
}

int insert(AVL *a, elem *x) {
  int c;
  int rValue = r_insert(&(a->root), x, &c);

  if(rValue == 0)
    (a->numElem)++;

  return rValue;
}
