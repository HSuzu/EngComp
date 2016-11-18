#include"matriz_esparsa.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() {
  Matrix m;
  initMatrix(&m);

  srand(time(NULL));

  int i = 0;
  while( i++ < 50000 ) {
    addElemAt(&m, rand(), rand());
  }
  addElemAt(&m, 1,1);
  removeElemAt(&m, 1,1);
  destroyMatrix(&m);
  return 0;
}
