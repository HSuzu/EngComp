/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

int main() {
  AVL a;
  cria(&a);

  char entrada[100];
  char *aux;
  if( fgets(entrada, 100, stdin) == NULL )
    return -1;

  aux = strtok(entrada, " ");

  int in = 0;
  while(aux != NULL) {
    in = atoi(aux);
    inserir(&a, &in);
    aux = strtok(NULL, " ");
  }

  if( fscanf(stdin, "%d", &in) < 1 )
    return -2;

  fprintf(stdout, "%d\n", pai(&a, &in));

  delete(a.raiz);
  return 0;
}
