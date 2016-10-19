#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define LIMIT 500
//#define DEBUG

int countSort(int *vector, int *output, int len, int k) {
  int *seq = (int *)malloc(sizeof(int)*k);
  if(!seq) return -1;

  int i;
  for(i = 0; i < k; i++) seq[i] = 0;
  for(i = 0; i < len; i++) seq[vector[i]]++;
  for(i = 1; i < k; i++) seq[i] += seq[i-1];
  for(i = len-1; i >= 0; i--) output[--seq[vector[i]]] = vector[i];

  free(seq);
  return 0;
}

void printVector(int *vector, int len, FILE *fd) {
  int i;
  for(i = 0; i < len-1; i++)
    fprintf(fd, "%d ", vector[i]);
  fprintf(fd, "%d\n", vector[i]);
}

void setRandomVector(int *vector, int len, int limit) {
  while(--len >= 0)
    vector[len] = rand()%limit;
}

int main() {
  srand(time(NULL));

#ifndef DEBUG
  clock_t dt;

  int i;
  for(i = 5000; i <= 150000; i += 500) {
    int *aux_in = (int *)malloc(sizeof(int) * i);
    if(!aux_in) {
      fprintf(stderr, "Memory error!\n");
      return -1;
    }
    int *aux_out = (int *)malloc(sizeof(int) * i);
    if(!aux_out) {
      fprintf(stderr, "Memory error!\n");
      free(aux_in);
      return -1;
    }

    setRandomVector(aux_in, i, LIMIT);

    dt = clock();
    countSort(aux_in, aux_out, i, LIMIT);
    dt = clock() - dt;

    fprintf(stdout, "%d %li\n", i, dt);

    free(aux_in);
    free(aux_out);
  }
#endif

#ifdef DEBUG
  int *aux_in = (int *)malloc(sizeof(int) * 20);
  if(!aux_in) {
  fprintf(stderr, "Memory error!\n");
  return -1;
  }
  int *aux_out = (int *)malloc(sizeof(int) * 20);
  if(!aux_out) {
  fprintf(stderr, "Memory error!\n");
  free(aux_in);
  return -1;
  }

  setRandomVector(aux_in, 20, LIMIT);
  countSort(aux_in, aux_out, 20, LIMIT);

  printVector(aux_in, 20, stdout);
  printVector(aux_out, 20, stdout);
  fprintf(stdout, "\n");

  free(aux_in);
  free(aux_out);
#endif

  return 0;
}
