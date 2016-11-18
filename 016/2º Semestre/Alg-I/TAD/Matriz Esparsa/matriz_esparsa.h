#ifndef _MATRIZ_ESPARSA_H
#define _MATRIZ_ESPARSA_H

typedef struct _node {
  int ID;
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
int linkNodeAfterColumn(Node *prev, int line, int column, int ID);
int linkNodeAfterLine(Node *prev, int line, int column, int ID);
int addElemAt(Matrix *m, int line, int column);
int isEmptyColumn(Node *node);
int isEmptyLine(Node *node);
int removeElemAt(Matrix *m, int line, int column);
void destroyMatrix(Matrix *m);

#endif
