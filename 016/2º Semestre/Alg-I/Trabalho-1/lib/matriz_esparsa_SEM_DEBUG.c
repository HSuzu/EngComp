/* Augusto Ribeiro Castro  - 9771421
 * Hiago De Franco Moreira - 9771289
 * Henry Shinji Suzukawa   - 9771504
*/

#include<stdio.h>
#include<stdlib.h>
#include "matriz_esparsa.h"
#include "avl.h"

// Inicia a matriz.
int initMatrix(Matrix *m) {
  Node *aux = (Node *)malloc(sizeof(Node));
  if(!aux)
    return -1;

  aux->line       = -1;
  aux->column     = -1;
  aux->nextLine   = aux;
  aux->nextColumn = aux;

  m->header = aux;

  return 0;
}

// Ajusta a posição para que fique uma matriz triangular superior, pois são ligações não direcionadas.
void toMatrixPos(int *line, int *column) {
  if(*line > *column) {
    int aux = *line;
    *line = *column;
    *column = aux;
  }
}

// Retona de uma lista horizontal o nó possivelmente anterior a uma coluna column.
Node **getColumnBefore(Node **header, int column) {
  // o header nem sempre terá valor -1... podemos chamar do meio da lista
  int headerValue = (*header)->column;
  // usar o header como sentinela... reduz comparações no while
  (*header)->column = column;

  Node **aux = header; // para não perder o header....
  while((*aux)->nextColumn->column < column)
    aux = &((*aux)->nextColumn);

  // Retorna ao valor original...
  (*header)->column = headerValue;

  return aux;
}

// Retorna de uma lista vertical o nó anterior a uma linha line.
Node **getLineBefore(Node **header, int line) {
  int headerValue = (*header)->line;
  (*header)->line = line;

  Node **aux = header;
  while((*aux)->nextLine->line < line)
    aux = &((*aux)->nextLine);

  (*header)->line = headerValue;

  return aux;
}

// Adiciona um elemento em uma lista horizontal depois de um elemento prev.
int linkNodeAfterColumn(Node *prev, int line, int column) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode)
    return -1;

  newNode->line   = line;
  newNode->column = column;

  newNode->nextColumn = prev->nextColumn;
  prev->nextColumn    = newNode;
  newNode->nextLine   = newNode;

  return 0;
}

// Adiciona um elemento em uma lista vertical depois de um elemento prev.
int linkNodeAfterLine(Node *prev, int line, int column) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode)
    return -1;

  newNode->line   = line;
  newNode->column = column;

  newNode->nextLine   = prev->nextLine;
  prev->nextLine      = newNode;
  newNode->nextColumn = newNode;

  return 0;
}

// Adiciona um elemento na posição.
int addElemAt(Matrix *m, int line, int column) {
  toMatrixPos(&line, &column); // ajusta posição

  Node **aux = getColumnBefore(&(m->header), column);

  if((*aux)->nextColumn->column != column) { // não existe a coluna
    if ( linkNodeAfterColumn(*aux, -1, column) < 0 ) // erro ao criar um novo nó no local desejado
      return -1;
  }

  aux = &((*aux)->nextColumn); // estamos na coluna correta

  aux = getLineBefore(aux, line);

  if((*aux)->nextLine->line == line) { // elemento já existe
    return 1;
  } else {
    if( linkNodeAfterLine(*aux, line, column) < 0 ) // erro ao criar um novo no no local desejado
      return -1;
  }

  Node *newNode = (*aux)->nextLine; // ponteiro para o novo elemento;

  // fará a ligação na linha
  aux = getLineBefore(&(m->header), line);
  if((*aux)->nextLine->line != line) { // linha não existe
    if ( linkNodeAfterLine(*aux, line, -1) < 0 ) // erro ao criar um novo no no local desejado
      return -1;
  }

  aux = &((*aux)->nextLine); // estamos na linha correta

  aux = getColumnBefore(aux, column);
  if((*aux)->nextColumn->column == column) // elemento já exite
    return 1;
  // ajustamos os ponteiros
  newNode->nextColumn = (*aux)->nextColumn;
  (*aux)->nextColumn = newNode;

  return 0;
}

// Verifica se uma lista vertical está vazia.
int isEmptyColumn(Node *node) {
  // basicamnte essa função anda dois elementos na lista e verifica se eles
  // são iguais a -1... ou seja, são cabeçalhos
  node = node->nextLine;
  if(node->line == -1 && node->nextLine->line == -1)
    return 1;

  return 0;
}

// Verifica se uma lista horizontal está vazia.
int isEmptyLine(Node *node) {
  node = node->nextColumn;
  if(node->column == -1 && node->nextColumn->column == -1)
    return 1;

  return 0;
}

// Remove um elemento em específico.
int removeElemAt(Matrix *m, int line, int column) {
  toMatrixPos(&line, &column); // corrige posição

  Node **aux_column = getColumnBefore(&(m->header), column);
  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    return -1; // elemento não encontrado
  }
  // estamos na coluna correta
  Node **aux_line = getLineBefore(aux_column, line);
  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    return -1; // elemento não encontrado
  }
  // estamos na linha correta
  // elemento encontrado..
  Node *rmNode = *aux_line; // no a ser removido
  *aux_line = (*aux_line)->nextLine; // desvincula rmNode da coluna

  Node *rmHeader = NULL;
  // testa se a coluna ficou vazia
  if(isEmptyColumn(*aux_line)) { // se sim, remove a coluna
    rmHeader = *aux_column;
    *aux_column = (*aux_column)->nextColumn;
    free(rmHeader);
  }

  // desvincularemos de uma linha
  aux_line = getLineBefore(&(m->header), line);
  if((*aux_line)->nextLine->line == line)
    aux_line = &((*aux_line)->nextLine);
  else {
    return -1; // elemento não encontrado
  }
  // estamos na linha correta
  aux_column = getColumnBefore(aux_line, column);
  if((*aux_column)->nextColumn->column == column)
    aux_column = &((*aux_column)->nextColumn);
  else {
    return -1; // elemento não encontrado
  }
  // desvincula o elemento
  *aux_column = (*aux_column)->nextColumn;
  // testa se a linha ficou vazia
  if(isEmptyLine(*aux_column)) { // se sim, exclui a linha
    rmHeader  = *aux_line;
    *aux_line = (*aux_line)->nextLine;
    free(rmHeader);
  }

  free(rmNode);

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

int degree(Matrix *m, int vertex) {
  //FEITO PARA UMA MATRIZ DIAGONAL!!!
  Node *aux = *(getLineBefore(&(m->header), vertex));
  aux = aux->nextLine;

  int count = 0;
  if(aux->line == vertex) {
    aux = aux->nextColumn;

    while(aux->column != -1) {
        count++;
        aux = aux->nextColumn;
    }
  }

  /*Como a matriz é diagonal, ela não armazena as ligações de elementos com id < linha em que você está.
  Assim, temos que somar toda a coluna cujo índice é igual ao de uma linha. Ex:
  -> Existe uma ligação de 1 com 3, logo existe uma de 3 com 1;
  -> Como 3 > 1, essa ligação só é representada na linha 1, mas influencia para o grau;
  -> Todas as ligações dessa forma estarão na coluna de índice igual a da linha.*/

  aux = *(getColumnBefore(&(m->header), vertex));
  aux = aux->nextColumn;

  if(aux->column == vertex) {
    aux = aux->nextLine;
    while(aux->line != -1) {
      count++;
      aux = aux->nextLine;
    }
  }

  return count;
}

float mediumDegree(Matrix *m, int vertex) {
  int neighbors = degree(m, vertex);

  //Se não existir o vértice pedido ou não existem ligações com o vétice(vide função grau):
  if(neighbors <= 0)
    return -1;

  Node *aux = *(getLineBefore(&(m->header), vertex));
  aux = aux->nextLine;

  int sum = 0;
  if(aux->line == vertex) {
    aux = aux->nextColumn; //sai dos sentinelas

    //Aqui já temos a linha do vértice e quantas ligações ele possui, basta somar o grau de cada vizinho:
    //Soma a linha:
    while(aux->column != -1) {
      sum += degree(m, aux->column);
      aux = aux->nextColumn;
    }
  }

  aux = *(getColumnBefore(&(m->header), vertex));
  aux = aux->nextColumn;

  if(aux->column == vertex) {
    aux = aux->nextLine;
    while(aux->line != -1) {
      sum += degree(m, aux->line);
      aux = aux->nextLine;
    }
  }

  return (sum/(float)neighbors);
}

int isConnectedWith(Matrix *m, int node, int vertex) {
  toMatrixPos(&node, &vertex);

  Node *nodeptr = *(getLineBefore(&(m->header), node));
  nodeptr = nodeptr->nextLine;
  if(nodeptr->line == node) {
    nodeptr = nodeptr->nextColumn;
    while(nodeptr->column != -1) {
      if(nodeptr->column == vertex)
        return 1;
      nodeptr = nodeptr->nextColumn;
    }
  }
  return 0;
}

int neighborsConnections(Matrix *m, int vertex) {
  int num = 0;

  Node *xptr; // o vertice com q vertex será ligado
  int x; // o número do vertice x

  Node *vtxptr = *(getColumnBefore(&(m->header), vertex));
  vtxptr = vtxptr->nextColumn;

  if(vtxptr->column == vertex) { // a coluna existe
    vtxptr = vtxptr->nextLine;

    while(vtxptr->line != -1) { // percorre as ligações
      x = vtxptr->line;
      xptr = *(getLineBefore(&(m->header), x));
      xptr = xptr->nextLine;
      if(xptr->line == x) {
        xptr = xptr->nextColumn;
        while(xptr->column != vertex) { // percorre as ligações de x do vertice até o sentinela (vertex está ligado com x)
          if(isConnectedWith(m, xptr->column, vertex))
            num++;
          xptr = xptr->nextColumn;
        }

        xptr = xptr->nextColumn;
        while(xptr->column != -1) { // aqui não teremos q pular a conexão com vertex
          if(isConnectedWith(m, xptr->column, vertex))
          num++;
          xptr = xptr->nextColumn;
        }
      }

      vtxptr = vtxptr->nextLine;
    }
  }

  vtxptr = *(getLineBefore(&(m->header), vertex));
  vtxptr = vtxptr->nextLine;

  if(vtxptr->line == vertex) { // a linha existe
    vtxptr = vtxptr->nextColumn; // sai do sentinela

    while(vtxptr->column != -1) { // percorre as ligações de 'x'.
      x = vtxptr->column; // seta a ligação q estamos
      xptr = *(getLineBefore(&(m->header), x));
      xptr = xptr->nextLine;
      if(xptr->line == x) {
        xptr = xptr->nextColumn;
        while(xptr->column != -1) { // aqui não teremos q pular a conexão com vertex
          if(isConnectedWith(m, xptr->column, vertex))
            num++;

          xptr = xptr->nextColumn;
        }
      }

      vtxptr = vtxptr->nextColumn; // passa para a prox ligação
    }
  }

  return num;
}

float clusteringCoeff(Matrix *m, int vertex) {
  int den = degree(m, vertex);
  den *= (den-1);

  //Se não existir o vértice pedido ou não existem ligações com o vétice(vide função grau):
  if(den <= 0)
    return den;

  int num = neighborsConnections(m, vertex);

  //Denominador realmente setado como grau*(grau-1):
  //Resultado: 2*num/den:
  return (2.0*(num/(float)den));
}

int hierarchicalDegree(Matrix *m, int vertex) {
  /*Utiliza uma AVL auxiliar para a contagem. A estrutura armazena todos os
  vértices com distância h = 2 de vertex, a fim de eliminar a contagem de
  polígonos formados pelo grafo.*/
  AVL a;
  create(&a);

  Node *xptr; // o vertice 'x' com q vertex será ligado.
  int x; // o número do vertice x

  Node *vtxptr = *(getColumnBefore(&(m->header), vertex));
  vtxptr = vtxptr->nextColumn;

  if(vtxptr->column == vertex) { // a coluna existe
    vtxptr = vtxptr->nextLine;

    while(vtxptr->line != -1) { // percorre as ligações
      x = vtxptr->line;

      xptr = *(getColumnBefore(&(m->header), x));
      xptr = xptr->nextColumn;
      if(xptr->column == x) {
        xptr = xptr->nextLine;
        while(xptr->line != -1) { // percorre as ligações de x do vertice até o sentinela (vertex está ligado com x)
          if(!isConnectedWith(m, xptr->line, vertex))
            insert(&a, &(xptr->line));
          xptr = xptr->nextLine;
        }
      }

      xptr = *(getLineBefore(&(m->header), x));
      xptr = xptr->nextLine;
      if(xptr->line == x) {
        xptr = xptr->nextColumn;
        while(xptr->column != vertex) { // percorre as ligações de x do vertice até o sentinela (vertex está ligado com x)
          if(!isConnectedWith(m, xptr->column, vertex))
            insert(&a, &(xptr->column));
          xptr = xptr->nextColumn;
        }

        xptr = xptr->nextColumn;
        while(xptr->column != -1) { // aqui não teremos q pular a conexão com vertex
          if(!isConnectedWith(m, xptr->column, vertex))
            insert(&a, &(xptr->column));
          xptr = xptr->nextColumn;
        }
      }

      vtxptr = vtxptr->nextLine;
    }
  }

  vtxptr = *(getLineBefore(&(m->header), vertex));
  vtxptr = vtxptr->nextLine;

  if(vtxptr->line == vertex) { // a linha existe
    vtxptr = vtxptr->nextColumn; // sai do sentinela

    while(vtxptr->column != -1) { // percorre as ligações de 'x'.
      x = vtxptr->column; // seta a ligação q estamos

      xptr = *(getColumnBefore(&(m->header), x));
      xptr = xptr->nextColumn;
      if(xptr->column == x) {
        xptr = xptr->nextLine;
        while(xptr->line != vertex) { // percorre as ligações de x do vertice até o sentinela (vertex está ligado com x)
          if(!isConnectedWith(m, xptr->line, vertex))
            insert(&a, &(xptr->line));
          xptr = xptr->nextLine;
        }

        xptr = xptr->nextLine;
        while(xptr->line != -1) { // aqui não teremos q pular a conexão com vertex
          if(!isConnectedWith(m, xptr->line, vertex))
            insert(&a, &(xptr->line));
          xptr = xptr->nextLine;
        }
      }


      xptr = *(getLineBefore(&(m->header), x));
      xptr = xptr->nextLine;
      if(xptr->line == x) {
        xptr = xptr->nextColumn;
        while(xptr->column != -1) { // aqui não teremos q pular a conexão com vertex
          if(!isConnectedWith(m, xptr->column, vertex))
            insert(&a, &(xptr->column));

          xptr = xptr->nextColumn;
        }
      }

      vtxptr = vtxptr->nextColumn; // passa para a prox ligação
    }
  }

  delete(a.root);
  return (a.numElem);
}
