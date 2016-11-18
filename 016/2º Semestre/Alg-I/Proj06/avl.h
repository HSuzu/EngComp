/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/
#ifndef AVL_H
#define AVL_H

typedef int elem;

typedef struct _no {
  struct _no *dir, *esq;
  int fb; // fator de balanceamento
  int info;
} no;

typedef struct _avl {
  no *raiz;
} AVL;

void cria(AVL *a);
void delete(no *a);
int inserir(AVL *a, elem *x);
int isAVL(no *raiz);

#endif
