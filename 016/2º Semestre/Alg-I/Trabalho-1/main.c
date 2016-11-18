/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/

#include<stdio.h>
#include<stdlib.h>
#include"lib/matriz_esparsa.h"

int main(void) {
  Matrix m;
  initMatrix(&m);

  int numVertex, numEdge;

  if( fscanf(stdin, "%d %d\n", &numVertex, &numEdge) < 2 )
    return -1;

  int vertex = 0;
  while(numVertex-- > 0)
    fscanf(stdin, "%d\n", &vertex);

  int cvertex = 0;
  while(numEdge-- > 0) {
    if( fscanf(stdin, "%d %d\n", &vertex, &cvertex) < 2 )
      return -1;
    addElemAt(&m, vertex, cvertex);
  }

  fscanf(stdin, "%d\n", &vertex);

  fprintf(stdout, "%d\n", degree(&m, vertex));
  fprintf(stdout, "%.2f\n", mediumDegree(&m, vertex));
  fprintf(stdout, "%.2f\n", clusteringCoeff(&m, vertex));
  fprintf(stdout, "%d\n", hierarchicalDegree(&m, vertex));

  destroyMatrix(&m);
  return 0;
}
