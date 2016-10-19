#include<stdio.h>
#include<stdlib.h>

//#define DEBUG

void printVector(int *vector, int len, FILE *fd) {
  int i;
  for(i = 0; i < len-1; i++)
    fprintf(fd, "%d ", vector[i]);
  fprintf(fd, "%d\n", vector[i]);
}

void printMatrix(int **matrix, int line, int column, FILE *fd) {
  int i;
  for(i = 0; i < line; i++)
    printVector(matrix[i], column, fd);

  fprintf(stdout, "\n");
}

void destroyMatrix(int **matrix, int line) {
  while(--line >= 0) free(matrix[line]);
  free(matrix);
}

void clearVector(int *vector, int len) {
  while(--len >= 0) vector[len] = 0;
}

void clearMatrix(int **matrix, int line, int column) {
  while(--line >= 0) clearVector(matrix[line], column);
}

int **createMatrix(int line, int column) {
  int **matrix = (int **)malloc(sizeof(int *)*line);
  if(!matrix) {
    return NULL;
  }

  int i = 0;
  while(i < line &&
    NULL != (matrix[i] = (int *)malloc(sizeof(int)*column)))
      i++;

  if(i < line && matrix[i] == NULL) {
    destroyMatrix(matrix, i);
    return NULL;
  }
  return matrix;
}

void addQueen(int **result, int size, int x, int y, int n) {
  if(x < 0 || y < 0 || y >= size || x >= size) {
    fprintf(stderr, "Erro ao posicionar rainha %d\n", n);
    return;
  }

  result[y][x] = -1;

  int idx = 0;
  while(idx < y) result[idx++][x] += n;

  idx = y+1;
  while(idx < size) result[idx++][x] += n;

  idx = 0;
  while(idx < x) result[y][idx++] += n;

  idx = x+1;
  while(idx < size) result[y][idx++] += n;
  //------------------- diagonal
}

void removeQueen(int **result, int size, int x, int y, int n) {
  if(x < 0 || y < 0 || y >= size || x >= size) {
    fprintf(stderr, "Erro ao localizar rainha %d\n", n);
    return;
  }

  result[y][x] = 0;

  int idx = 0;
  while(idx < y) result[idx++][x] -= n;

  idx = y+1;
  while(idx < size) result[idx++][x] -= n;

  idx = 0;
  while(idx < x) result[y][idx++] -= n;

  idx = x+1;
  while(idx < size) result[y][idx++] -= n;
  //-----------------------diagonal
}

int queens(int **result, int size, int n) {
  if(n <= 0 || n > size) return 1;

  int y = 0;
  int r = 0;
  do {
    if(result[y][n] != 0) return 0;

    addQueen(result, size, n, y, n);
    r = queens(result, size, n);
    if(!r) {
      removeQueen(result, size, n, y, n);
      y++;
    }
  } while(!r);
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Adicione apos %s o tamanho do tabuleiro.\n", argv[0]);
    return 1;
  }

  int size = atoi(argv[1]);

  int **result = createMatrix(size, size);
  if(!result) {
    fprintf(stderr, "Erro ao criar tabuleiro (alocacao de memoria).\n");
    return -1;
  }

  destroyMatrix(result);
  return 0;
}
