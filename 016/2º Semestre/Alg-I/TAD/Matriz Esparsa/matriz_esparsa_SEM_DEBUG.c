#include<stdio.h>
#include<stdlib.h>
#include "matriz_esparsa.h"

// inicia a matriz
int initMatrix(Matrix *m) {
  Node *aux = (Node *)malloc(sizeof(Node));
  if(!aux)
    return -1;

  aux->ID         = -1;
  aux->line       = -1;
  aux->column     = -1;
  aux->nextLine   = aux;
  aux->nextColumn = aux;

  m->header = aux;

  aux = NULL;

  return 0;
}

// ajusta a posição para que fique uma matriz triangular
// superior... (pois são ligações não direcionadas)
void toMatrixPos(int *line, int *column) {
  if(*line < 0)
    *line = 0;

  if(*column < 0)
    *column = 0;

  if(*line > *column) {
    int aux = *line;
    *line = *column;
    *column = aux;
  }
}

// Ponteiro duplo para ajudar na remoção...
// (não ter um ponteiro auxiliar do anterior)
// retona de uma lista horizontal o nó possivelmente anterior
// a uma coluna column
Node **getColumnBefore(Node **header, int column) {
  /* Pensar sobre o caso da coluna/linha ser -1....
   * ^- se a coluna for -1 teremos que passar pela lista inteira
   */
  if(!header)
    return NULL;


  // agora sabemos um jeito melhor de fazer isso, façamos...
  int headerValue = (*header)->column; // para ter certeza de que o valor
                                      // será constante
  // usar o header como sentinela... reduz comparações no while
  (*header)->column = column;

  Node **aux = header; // para não perder o header....
  while((*aux)->nextColumn->column < column) // será que é muito dispendioso?
    aux = &((*aux)->nextColumn);

  (*header)->column = headerValue;

  return aux;
}

// retorna de uma lista vertical o nó possivelmente anterior
// a uma linha line
Node **getLineBefore(Node **header, int line) {
  if(!header)
    return NULL;

  int headerValue = (*header)->line;
  (*header)->line = line;

  Node **aux = header;
  while((*aux)->nextLine->line < line)
    aux = &((*aux)->nextLine);

  (*header)->line = headerValue;

  return aux;
}

// adiciona um elemento em uma lista horizontal depois de um elemento prev.
int linkNodeAfterColumn(Node *prev, int line, int column, int ID) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode)
    return -1;

  newNode->line   = line;
  newNode->column = column;
  newNode->ID     = ID;

  newNode->nextColumn = prev->nextColumn;
  prev->nextColumn    = newNode;
  newNode->nextLine   = newNode;

  newNode = NULL;

  return 0;
}

// adiciona um elemento em uma lista vertical depois de um elemento prev
int linkNodeAfterLine(Node *prev, int line, int column, int ID) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode)
    return -1;

  newNode->line   = line;
  newNode->column = column;
  newNode->ID     = ID;

  newNode->nextLine   = prev->nextLine;
  prev->nextLine      = newNode;
  newNode->nextColumn = newNode;

  newNode = NULL;

  return 0;
}

// adiciona um elemento na posição ....
int addElemAt(Matrix *m, int line, int column) {
  toMatrixPos(&line, &column);

  Node **aux = getColumnBefore(&(m->header), column);
  if(!aux)
    return -1;

  // Non-permanent FIX -----------------------------------------------------------------------------
  if((*aux)->nextColumn->column != column) {
    if ( linkNodeAfterColumn(*aux, -1, column, -1) < 0 ) { // erro ao criar um novo no no local desejado
      aux = NULL;
      return -2;
    }
  }

  aux = &((*aux)->nextColumn);

  aux = getLineBefore(aux, line);
  if(!aux)
    return -1;

  if((*aux)->nextLine->line == line) {
    aux = NULL;
    return 1; // elemento já existe
  } else {
    if( linkNodeAfterLine(*aux, line, column, 0) < 0 ) { // erro ao criar um novo no no local desejado
      aux = NULL;
      return -2;
    }
  }

  Node *newNode = (*aux)->nextLine; // ponteiro para o novo elemento;
  // fará a ligação na linha
  aux = getLineBefore(&(m->header), line);
  if(!aux)
    return -1;

  // Non-permanent FIX -----------------------------------------------------------------------------
  if((*aux)->nextLine->line != line) {
    if ( linkNodeAfterLine(*aux, line, -1, -1) < 0 ) { // erro ao criar um novo no no local desejado
      newNode = NULL;
      aux = NULL;
      return -2;
    }
  }

  aux = &((*aux)->nextLine);

  aux = getColumnBefore(aux, column);
  if(!aux)
    return -1;

  if((*aux)->nextColumn->column == column) {
    newNode = NULL;
    aux = NULL;
    return -3;
  }

  newNode->nextColumn = (*aux)->nextColumn;
  (*aux)->nextColumn = newNode;

  newNode = NULL;
  aux = NULL;
  return 0;
}

// verifica se uma lista vertical está vazia
int isEmptyColumn(Node *node) {
  if(!node)
    return -1;
  // testa se só tem o header... será q há algum jeito mais bonito?
  if(node->nextLine->line == -1 && node->nextLine->nextLine->line == -1)
    return 1;

  return 0;
}

// verifica se uma lista horizontal está vazia
int isEmptyLine(Node *node) {
  if(!node)
    return -1;
  // testa se só tem o header... será q há algum jeito mais bonito?
  if(node->nextColumn->column == -1 && node->nextColumn->nextColumn->column == -1)
    return 1;

  return 0;
}

// remove um elemento em específico
int removeElemAt(Matrix *m, int line, int column) {
  toMatrixPos(&line, &column);

  Node **aux_column = getColumnBefore(&(m->header), column);
  if(!aux_column)
    return -1;

  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    aux_column = NULL;
    return -1; // elemento não encontrado
  }

  // bom, pq nao usar o mesmo ponteiro?....
  // entao... e se houver só um elemento?
  Node **aux_line = getLineBefore(aux_column, line);
  if(!aux_line) {
    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }
  // elemento encontrado..
  Node *rmNode = *aux_line; // no a ser removido
  *aux_line = (*aux_line)->nextLine; // desvincula rmNode da coluna

  Node *rmHeader = NULL;
  // testa se só tem o header... será q há algum jeito mais bonito?
  if(isEmptyColumn(*aux_line)) {
    rmHeader = *aux_column;
    *aux_column = (*aux_column)->nextColumn;
    free(rmHeader); // < ---------------------------- isso está certo??????????
  }

  aux_line = getLineBefore(&(m->header), line);

  if(!aux_line) {
    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }

  aux_column = getColumnBefore(aux_line, column);

  if(!aux_column) {
    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }

  *aux_column = (*aux_column)->nextColumn;

  if(isEmptyLine(*aux_column)) {
    rmHeader  = *aux_line;
    *aux_line = (*aux_line)->nextLine;
    free(rmHeader);
  }

  free(rmNode);

  rmHeader   = NULL;
  rmNode     = NULL;
  aux_column = NULL;
  aux_line   = NULL;

  return 0;
}

void destroyMatrix(Matrix *m) {
  Node *current, *nextLine, *nextColumn;
  current    = m->header->nextColumn;
  nextColumn = current->nextColumn;

  current    = current->nextLine;
  nextLine   = current->nextLine;

  m->header = NULL;

  while(current->column != -1) {
    while(current->line != -1) {
      free(current);
      current = nextLine;
      nextLine = nextLine->nextLine;
    }
    free(current);
    current = nextColumn->nextLine;
    nextLine = current->nextLine;
    nextColumn = nextColumn->nextColumn;
  }
  while(current->line != -1) {
    free(current);
    current = nextLine;
    nextLine = nextLine->nextLine;
  }

  free(current);
}
