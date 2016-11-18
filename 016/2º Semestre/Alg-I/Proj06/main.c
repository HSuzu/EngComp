/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/
#include<stdio.h>
#include<stdlib.h>
#include "avl.h"

int main() {
  AVL a;
  cria(&a);

  int in;
  while(fscanf(stdin, "%d", &in) == 1) {
    inserir(&a, &in);
  }

  fprintf(stdout, "%d\n", isAVL(a.raiz));
  delete(a.raiz);
  return 0;
}
