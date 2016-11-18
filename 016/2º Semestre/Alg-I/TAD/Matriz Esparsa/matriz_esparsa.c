#include<stdio.h>
#include<stdlib.h>
#include "matriz_esparsa.h"

#define DEBUGMSG

// inicia a matriz
int initMatrix(Matrix *m) {

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] initMatrix was caled with (%p) as argument\n", m);
  #endif

  Node *aux = (Node *)malloc(sizeof(Node));
  if(!aux) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] initMatrix fail due to insufficient memory (malloc return NULL)\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] initMatrix succesfuly create an new node %p\n", aux);
  #endif

  aux->ID         = -1;
  aux->line       = -1;
  aux->column     = -1;
  aux->nextLine   = aux;
  aux->nextColumn = aux;

  m->header = aux;

  aux = NULL;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] initMatrix reached end with no errors. Return value 0\n\n");
  #endif

  return 0;
}

// ajusta a posição para que fique uma matriz triangular
// superior... (pois são ligações não direcionadas)
void toMatrixPos(int *line, int *column) {

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] toMatrixPos was caled with the values (%d, %d)\n", *line, *column);
  #endif

  if(*line < 0)
    *line = 0;

  if(*column < 0)
    *column = 0;

  if(*line > *column) {
    int aux = *line;
    *line = *column;
    *column = aux;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] toMatrixPos determined that the correct values to position is l: %d; c: %d\n", *line, *column);
  fprintf(stderr, "[INFO] toMatrixPos reached the end with no errors. Return value (void)\n\n");
  #endif
}

// Ponteiro duplo para ajudar na remoção...
// (não ter um ponteiro auxiliar do anterior)
// retona de uma lista horizontal o nó possivelmente anterior
// a uma coluna column
Node **getColumnBefore(Node **header, int column) {
  /* Pensar sobre o caso da coluna/linha ser -1....
   * ^- se a coluna for -1 teremos que passar pela lista inteira
   */

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getColumnBefore was called with (%p, %d) as parameters.\n", header, column);
  #endif

  if(!header) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] getColumnBefore receives an NULL pointer.\n\n");
    #endif

    return NULL;
  }

  #ifdef DEBUGMSG
  if((*header)->column != -1) {
    fprintf(stderr, "[WARNING] getColumnBefore receives an non-negative header.\n");
  } else {
    fprintf(stderr, "[INFO] getColumnBefore receives an negative header\n");
  }
  #endif

  // agora sabemos um jeito melhor de fazer isso, façamos...
  int headerValue = (*header)->column; // para ter certeza de que o valor
                                      // será constante
  // usar o header como sentinela... reduz comparações no while
  (*header)->column = column;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getColumnBefore has seted header with value %d\n", column);
  #endif

  Node **aux = header; // para não perder o header....

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getColumnBefore will test an element with value %d\n", (*aux)->nextColumn->column);
  #endif

  while((*aux)->nextColumn->column < column) { // será que é muito dispendioso?
    aux = &((*aux)->nextColumn);

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] getColumnBefore will test an element with value %d\n", (*aux)->nextColumn->column);
    #endif

  }

  (*header)->column = headerValue;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getColumnBefore has seted header with value %d\n", headerValue);
  fprintf(stderr, "[INFO] getColumnBefore has reached end with no errors. Returned value %p\n\n", aux);
  #endif

  return aux;
}

// retorna de uma lista vertical o nó possivelmente anterior
// a uma linha line
Node **getLineBefore(Node **header, int line) {

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getLineBefore was called with (%p, %d) as parameters\n", header, line);
  #endif

  if(!header) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] getLineBefore receives an NULL pointer.\n\n");
    #endif

    return NULL;
  }

  #ifdef DEBUGMSG
  if((*header)->line != -1) {
    fprintf(stderr, "[WARNING] getLineBefore receives an non-negative header.\n");
  } else {
    fprintf(stderr, "[INFO] getLineBefore receives an negative header.\n");
  }
  #endif

  int headerValue = (*header)->line;
  (*header)->line = line;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getLineBefore has seted header with value %d\n", line);
  #endif

  Node **aux = header;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getLineBefore will test an element with value %d\n", (*aux)->nextLine->line);
  #endif

  while((*aux)->nextLine->line < line) {
    aux = &((*aux)->nextLine);

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] getLineBefore will test an element with value %d\n", (*aux)->nextLine->line);
    #endif

  }

  (*header)->line = headerValue;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] getLineBefore has seted header with value %d\n", headerValue);
  fprintf(stderr, "[INFO] getLineBefore has reached end with no errors. Returned value %p.\n\n", aux);
  #endif

  return aux;
}

// adiciona um elemento em uma lista horizontal depois de um elemento prev.
int linkNodeAfterColumn(Node *prev, int line, int column, int ID) {

  #ifdef DEBUGMSG
  fprintf(stderr, "linkNodeAfterColumn was called with (%p, %d, %d, %d) as parameters.\n", prev, line, column, ID);
  #endif

  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] linkNodeAfterColumn fail due to insufficient memory (malloc return NULL).\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] linkNodeAfterColumn succeeded at creating an newNode.\n");
  #endif

  newNode->line   = line;
  newNode->column = column;
  newNode->ID     = ID;

  newNode->nextColumn = prev->nextColumn;
  prev->nextColumn    = newNode;
  newNode->nextLine   = newNode;

  newNode = NULL;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] linkNodeAfterColumn has seted the values of the newNode.\n");
  fprintf(stderr, "[INFO] linkNodeAfterColumn has reached end with no errors. Returned value 0.\n\n");
  #endif

  return 0;
}

// adiciona um elemento em uma lista vertical depois de um elemento prev
int linkNodeAfterLine(Node *prev, int line, int column, int ID) {

  #ifdef DEBUGMSG
  fprintf(stderr, "linkNodeAfterLine was called with (%p, %d, %d, %d) as parameters.\n", prev, line, column, ID);
  #endif

  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] linkNodeAfterLine fail due to insufficient memory (malloc return NULL)\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] linkNodeAfterLine succeeded at creating an newNode.\n");
  #endif

  newNode->line   = line;
  newNode->column = column;
  newNode->ID     = ID;

  newNode->nextLine   = prev->nextLine;
  prev->nextLine      = newNode;
  newNode->nextColumn = newNode;

  newNode = NULL;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] linkNodeAfterLine has seted the values of the newNode.\n");
  fprintf(stderr, "[INFO] linkNodeAfterLine has reached end with no errors. Returned value 0.\n\n");
  #endif

  return 0;
}

// adiciona um elemento na posição ....
int addElemAt(Matrix *m, int line, int column) {
  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt was called with (%p, %d, %d) as parameters.\n", m, line, column);
  fprintf(stderr, "[INFO] addElemAt will call toMatrixPos\n...\n");
  #endif

  toMatrixPos(&line, &column);

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt will call getColumnBefore\n...\n");
  #endif

  Node **aux = getColumnBefore(&(m->header), column);

  if(!aux) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] addElemAt receives an NULL pointer from getColumnBefore.\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt receives %p from getColumnBefore.\n", aux);
  #endif

  // Non-permanent FIX -----------------------------------------------------------------------------
  if((*aux)->nextColumn->column != column) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] addElemAt will call linkNodeAfterColumn.\n...\n");
    #endif

    if ( linkNodeAfterColumn(*aux, -1, column, -1) < 0 ) { // erro ao criar um novo no no local desejado
      #ifdef DEBUGMSG
      fprintf(stderr, "[ERROR] addElemAt couldn't link a new node\n\n");
      #endif

      aux = NULL;
      return -2;
    }
  }

  aux = &((*aux)->nextColumn);

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt has reached the resquested column %d.\n", column);
  fprintf(stderr, "[INFO] addElemAt will call getLineBefore\n...\n");
  #endif

  aux = getLineBefore(aux, line);

  if(!aux) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] addElemAt receives an NULL pointer from getLineBefore.\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt receives %p from getLineBefore.\n", aux);
  #endif

  if((*aux)->nextLine->line == line) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[WARNING] addElemAt couldn't add an element because it already exists\n\n");
    #endif

    aux = NULL;
    return 1; // elemento já existe
  } else {

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] addElemAt will call linkNodeAfterLine\n...\n");
    #endif

    if( linkNodeAfterLine(*aux, line, column, 0) < 0 ) { // erro ao criar um novo no no local desejado
      #ifdef DEBUGMSG
      fprintf(stderr, "[ERROR] addElemAt couldn't link a new node\n\n");
      #endif

      aux = NULL;
      return -2;
    }
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt succesfuly create an new node.\n");
  #endif

  Node *newNode = (*aux)->nextLine; // ponteiro para o novo elemento;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt will call getLineBefore\n...\n");
  #endif

  // fará a ligação na linha
  aux = getLineBefore(&(m->header), line);
  if(!aux) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] addElemAt receives an NULL pointer from getLineBefore.\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt receives %p from getLineBefore.\n", aux);
  #endif

  // Non-permanent FIX -----------------------------------------------------------------------------
  if((*aux)->nextLine->line != line) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] addElemAt will call linkNodeAfterLine\n...\n");
    #endif

    if ( linkNodeAfterLine(*aux, line, -1, -1) < 0 ) { // erro ao criar um novo no no local desejado
      #ifdef DEBUGMSG
      fprintf(stderr, "[ERROR] addElemAt couldn't link a new node\n\n");
      #endif

      newNode = NULL;
      aux = NULL;
      return -2;
    }
  }

  aux = &((*aux)->nextLine);

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt reached the element line.\n...\n");
  fprintf(stderr, "[INFO] addElemAt will call getColumnBefore.\n...\n");
  #endif

  aux = getColumnBefore(aux, column);

  if(!aux) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] addElemAt receives an NULL pointer from getColumnBefore.\n\n");
    #endif
    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt receives %p from getColumnBefore.\n", aux);
  #endif

  if((*aux)->nextColumn->column == column) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[CRITICAL ERROR] addElemAt couldn't add an element because it already exists\n\n");
    #endif

    newNode = NULL;
    aux = NULL;
    return -3;
  }

  newNode->nextColumn = (*aux)->nextColumn;
  (*aux)->nextColumn = newNode;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] addElemAt has add the resquested element l: %d; c:%d.\n", line, column);
  fprintf(stderr, "[INFO] addElemAt has reached the end. Returned value 0\n\n");
  #endif

  newNode = NULL;
  aux = NULL;
  return 0;
}

// verifica se uma lista vertical está vazia
int isEmptyColumn(Node *node) {
  #ifdef DEBUGMSG
  fprintf(stderr, "isEmptyColumn was called with (%p) as parameter.\n", node);
  #endif

  if(!node) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] isEmptyColumn receives an NULL pointer as an argument.\n\n");
    #endif

    return -1;
  }

  // testa se só tem o header... será q há algum jeito mais bonito?
  if(node->nextLine->line == -1 && node->nextLine->nextLine->line == -1) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] isEmptyColumn determined that the column IS empty.\n");
    fprintf(stderr, "[INFO] isEmptyColumn reached end. Returned value 1.\n\n");
    #endif

    return 1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] isEmptyColumn determined that the column ISN'T empty.\n");
  fprintf(stderr, "[INFO] isEmptyColumn reached end. Returned value 0.\n\n");
  #endif

  return 0;
}

// verifica se uma lista horizontal está vazia
int isEmptyLine(Node *node) {

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] isEmptyLine was called with (%p) as parameter.\n", node);
  #endif

  if(!node) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] isEmptyLine receives an NULL pointer as an argument.\n\n");
    #endif

    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] isEmptyLine receives %p as an argument.\n", node);
  #endif

  // testa se só tem o header... será q há algum jeito mais bonito?
  if(node->nextColumn->column == -1 && node->nextColumn->nextColumn->column == -1) {

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] isEmptyLine determined that the column IS empty.\n");
    fprintf(stderr, "[INFO] isEmptyLine reached end. Returned value 1.\n\n");
    #endif

    return 1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] isEmptyLine determined that the column ISN'T empty.\n");
  fprintf(stderr, "[INFO] isEmptyLine reached end. Returned value 0.\n\n");
  #endif

  return 0;
}

// remove um elemento em específico
int removeElemAt(Matrix *m, int line, int column) {

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt was called with (%p, %d, %d) as parameters.\n", m, line, column);
  fprintf(stderr, "[INFO] removeElemAt will call toMatrixPos\n...\n");
  #endif

  toMatrixPos(&line, &column);

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt will call getColumnBefore.\n...\n");
  #endif

  Node **aux_column = getColumnBefore(&(m->header), column);

  if(!aux_column) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt receives an NULL pointer from getColumnBefore.\n\n");
    #endif

    return -1;
  }

  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt couldn't locate the resquested element.\n\n");
    #endif

    aux_column = NULL;
    return -1; // elemento não encontrado
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt succeeded in locate the element inside a column.\n");
  #endif

  // bom, pq nao usar o mesmo ponteiro?....
  // entao... e se houver só um elemento?

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt will call getLineBefore.\n...\n");
  #endif

  Node **aux_line = getLineBefore(aux_column, line);

  if(!aux_line) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt receives an NULL pointer from getLineBefore.\n\n");
    #endif

    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt couldn't locate the resquested element.\n\n");
    #endif

    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt succeeded in locate the element.\n");
  #endif

  // elemento encontrado..
  Node *rmNode = *aux_line; // no a ser removido
  *aux_line = (*aux_line)->nextLine; // desvincula rmNode da coluna

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt remove the element at a column.\n");
  #endif

  Node *rmHeader = NULL;
  // testa se só tem o header... será q há algum jeito mais bonito?
  if(isEmptyColumn(*aux_line)) {
    rmHeader = *aux_column;
    *aux_column = (*aux_column)->nextColumn;
    free(rmHeader); // < ---------------------------- isso está certo??????????

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] removeElemAt remove the column header.\n");
    #endif

  }

  aux_line = getLineBefore(&(m->header), line);

  if(!aux_line) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt receives an NULL pointer from getLineBefore.\n\n");
    #endif

    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt receives %p from getLineBefore.\n", aux_line);
  #endif

  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt couldn't locate the resquested element.\n\n");
    #endif

    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt succeeded in locate the element inside a line.\n");
  #endif

  aux_column = getColumnBefore(aux_line, column);

  if(!aux_column) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt receives an NULL pointer from getColumnBefore.\n\n");
    #endif

    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt receives %p from getColumnBeforeBefore.\n", aux_column);
  #endif

  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    #ifdef DEBUGMSG
    fprintf(stderr, "[ERROR] removeElemAt couldn't locate the resquested element.\n\n");
    #endif

    rmHeader   = NULL;
    rmNode     = NULL;
    aux_column = NULL;
    aux_line   = NULL;
    return -1; // elemento não encontrado
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt succeeded in locate the element inside a column.\n");
  #endif

  *aux_column = (*aux_column)->nextColumn;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt removed the elementfrom a line.\n");
  #endif

  if(isEmptyLine(*aux_column)) {
    rmHeader  = *aux_line;
    *aux_line = (*aux_line)->nextLine;
    free(rmHeader);

    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] removeElemAt removed a line header.\n");
    #endif
  }

  free(rmNode);

  rmHeader   = NULL;
  rmNode     = NULL;
  aux_column = NULL;
  aux_line   = NULL;

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] removeElemAt reached end. Return value 0.\n\n");
  #endif

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
      #ifdef DEBUGMSG
      fprintf(stderr, "[INFO] destroyMatrix removed l: %d; c: %d\n", current->line, current->column);
      #endif

      free(current);
      current = nextLine;
      nextLine = nextLine->nextLine;
    }
    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] destroyMatrix removed l: %d; c: %d\n", current->line, current->column);
    #endif

    free(current);
    current = nextColumn->nextLine;
    nextLine = current->nextLine;
    nextColumn = nextColumn->nextColumn;
  }

  while(current->line != -1) {
    #ifdef DEBUGMSG
    fprintf(stderr, "[INFO] destroyMatrix removed l: %d; c: %d\n", current->line, current->column);
    #endif

    free(current);
    current = nextLine;
    nextLine = nextLine->nextLine;
  }

  #ifdef DEBUGMSG
  fprintf(stderr, "[INFO] destroyMatrix removed l: %d; c: %d\n", current->line, current->column);
  #endif

  free(current);
}
