/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/

#ifndef AVL_H
#define AVL_H

typedef int elem;

typedef struct _NodeAVL {
  struct _NodeAVL *right, *left;
  int bf; // fator de balanceamento
  int info;
} NodeAVL;

typedef struct _AVL {
  NodeAVL *root;
  int numElem;
} AVL;

void create(AVL *a);
void delete(NodeAVL *a);
int insert(AVL *a, elem *x);
int r_insert(NodeAVL **r, elem *x, int *c);

#endif
