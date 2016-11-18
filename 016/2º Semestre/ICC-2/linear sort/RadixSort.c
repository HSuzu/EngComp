#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define LIMIT 10
#define DIGITS 4
//#define DEBUG

void cpVector(int *src, int *dest, int len) {
  while(--len >= 0) dest[len] = src[len];
}

void cpMatrix(int **src, int **dest, int line, int column) {
  while(--line >= 0) cpVector(src[line], dest[line], column);
}

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

void setRandomVector(int *vector, int len, int limit) {
  while(--len >= 0)
    vector[len] = rand()%limit;
}

void setRandomMatrix(int **matrix, int line, int column, int limit) {
  while(--line >= 0)
    setRandomVector(matrix[line], column, limit);
}

void destroyMatrix(int **matrix, int line) {
  while(--line >= 0) free(matrix[line]);
  free(matrix);
}

int** createMatrix(int line, int column) {
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

int countSort(int **vector, int **output, int column, int line, int len_col, int k) {
  int *seq = (int *)malloc(sizeof(int)*k);
  if(!seq) {
    fprintf(stderr, "Memory Error!\n");
    return -1;
  }

  column--; // column starts with 1, we must have column 0

  int i;
  for(i = 0; i < k; i++) seq[i] = 0;
  for(i = 0; i < line; i++) seq[ vector[i][column] ]++;
  for(i = 1; i < k; i++) seq[i] += seq[i-1];
  for(i = line-1; i >= 0; i--)
    cpVector(vector[i], output[ --seq[ vector[i][column]] ], len_col);

  free(seq);
  return 0;
}

int radixSort(int **vector, int line, int column, int k) {
  int **output = createMatrix(line, column);
  if(!output) {
    fprintf(stderr, "Memory error!\n");
    return -1;
  }

  int i = column;
  while(i > 0) {
    if( countSort(vector, output, i, line, column, k) < 0 )
      return -1;
    i--;
    cpMatrix(output, vector, line, column);
  }

  destroyMatrix(output, line);
  return 0;
}

int main() {
  srand(time(NULL));
#ifndef DEBUG
  clock_t dt;

  int i;
  for(i = 5000; i <= 150000; i += 500) {
    int **aux_in = createMatrix(i, DIGITS);
    if(!aux_in) {
      fprintf(stderr, "Memory error!\n");
      return -1;
    }

    setRandomMatrix(aux_in, i, DIGITS, LIMIT);

    dt = clock();
    radixSort(aux_in, i, DIGITS, LIMIT);
    dt = clock() - dt;

    fprintf(stdout, "%d %li\n", i, dt);

    destroyMatrix(aux_in, i);
  }
#endif

#ifdef DEBUG
  int **aux_in = createMatrix(20, DIGITS);
  if(!aux_in) {
    fprintf(stderr, "Memory error!\n");
    return -1;
  }

  setRandomMatrix(aux_in, 20, DIGITS, LIMIT);

  printMatrix(aux_in, 20, DIGITS, stdout);
  if( radixSort(aux_in, 20, DIGITS, LIMIT) < 0 )
    fprintf(stderr, "RADIX ERROR!\n");

  printMatrix(aux_in, 20, DIGITS, stdout);
  fprintf(stdout, "\n");

  destroyMatrix(aux_in, 20);
#endif
  return 0;
}
