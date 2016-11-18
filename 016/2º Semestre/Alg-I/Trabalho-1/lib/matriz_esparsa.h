/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/

#ifndef _MATRIZ_ESPARSA_H
#define _MATRIZ_ESPARSA_H

typedef struct _node {
  int line;
  int column;
  struct _node *nextLine;
  struct _node *nextColumn;
} Node;

typedef struct _matrix {
  Node *header;
} Matrix;

int initMatrix(Matrix *m);
void toMatrixPos(int *line, int *column);
Node **getColumnBefore(Node **header, int column);
Node **getLineBefore(Node **header, int line);
int linkNodeAfterColumn(Node *prev, int line, int column);
int linkNodeAfterLine(Node *prev, int line, int column);
int addElemAt(Matrix *m, int line, int column);
int isEmptyColumn(Node *node);
int isEmptyLine(Node *node);
int removeElemAt(Matrix *m, int line, int column);
void destroyMatrix(Matrix *m);
int degree(Matrix *m, int vertex);
float mediumDegree(Matrix *m, int vertex);
float clusteringCoeff(Matrix *m, int vertex);
int hierarchicalDegree(Matrix *m, int vertex);

#endif
