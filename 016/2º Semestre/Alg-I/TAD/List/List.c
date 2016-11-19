#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int initList(List *l, Operations *opts) {
  l->last   = NULL;
  numOfElem = 0;
  l->opts   = opts;

  Node *aux = (Node *)malloc(sizeof(Node));
  if(!aux) {
    #ifdef DEBUG_LIST
    fprintf(stderr, "[ERROR] failed to create header.\n");
    #endif

    l->header = NULL;
    return -1;
  }

  if( opts->setInvalidValue(aux->info) < 0 ) {
    #ifdef DEBUG_LIST
    fprintf(stderr, "[ERROR] failed set invalid value to header.\n");
    #endif
    return -2;
  }

  aux->next = aux;
  l->header = aux;
}

int isEmptyList(List *l) {
  if(l->first)
    return 0;
  return 1;
}

int addElemAt(List *l, void *elem, unsigned int position) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  if( l->opts->copy(elem, &(new_node->info)) < 0 ) {
    
  }

  Node *aux = l->first;
}
