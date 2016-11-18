#include <stdio.h>
#include <stdlib.h>

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

int **readMatrix(const char *path, int *line, int *column) {
  char *error;
  FILE *fd = fopen(path, "r");
  if(!fd) {
    error = "Erro ao ler arquivo!";
    goto err;
  }

  if( fscanf(fd, "%d %d", line, column) < 2 ) {
    error = "Erro ao ler arquivo!";
    goto err;
  }

  if(*line <= 0 || *column <= 0) {
    error = "Numero de linhas e/ou colunas invalido!";
    goto err;
  }

  int **matrix = createMatrix(*line, *column);
  if(!matrix) {
    error = "Erro ao criar matriz";
    goto err;
  }

  int i, j;
  for(j = 0; j < *line; j++) {
    for(i = 0; i < *column; i++) {
      if(fscanf(fd, "%d", &(matrix[j][i])) < 1 ) {
        fprintf(stderr, "Formatacao incorreta! Elemento (%d, %d) será nulo\n", i,j);
        matrix[j][i] = 0;
      }
    }
  }

  fclose(fd);
  return matrix;

err:
  fprintf(stderr, "%s\n", error);
  fclose(fd);
  return NULL;
}

int r_getExit(int **matrix, int line, int column, int x, int y, int **aux) {
  if(x < 0 || y < 0) return 0;
  if(x >= column || y >= line) return 0;
  if(aux[y][x]) return 0;
  if(matrix[y][x] == 0) return 0;

  aux[y][x] = 1;
  if(x == column-1 && y == line-1) {
    clearMatrix(aux, line, column);
    return 1;
  }

  if(!r_getExit(matrix, line, column, x+1, y, aux)) {
    if(!r_getExit(matrix, line, column, x, y+1, aux)) {
      if(!r_getExit(matrix, line, column, x-1, y, aux)) {
        if(!r_getExit(matrix, line, column, x, y-1, aux)) {
          return 0;
        }
      }
    }
  }
  fprintf(stdout, "(%d, %d)\n", x, y);
  aux[y][x] = 1;
  return 1;
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Insira o caminho do arquivo a ser lido\n");
    return -1;
  }

  int line = 0;
  int column = 0;
  int **matrix = readMatrix(argv[1], &line, &column);

  int **aux = createMatrix(line, column);
  if(!aux) {
    fprintf(stderr, "Erro ao criar matriz\n");
    destroyMatrix(matrix, line);
    return -1;
  }

  clearMatrix(aux, line, column);

#ifdef DEBUG
  fprintf(stdout, "lines: %d\ncolumn: %d\n", line, column);

  printMatrix(matrix, line, column, stdout);
#endif

  int result = r_getExit(matrix, line, column, 0, 0, aux);

  if(result) {
    fprintf(stdout, "Sucesso!:\n");
    printMatrix(aux, line, column, stdout);
  } else {
    fprintf(stdout, "Falha!\n");
  }

  destroyMatrix(matrix, line);
  destroyMatrix(aux, line);
  return 0;
}
