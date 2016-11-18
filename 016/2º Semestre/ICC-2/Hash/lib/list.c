#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criaList(List *list) {
  list->inicio = NULL;
  list->tam = 0;
}

int addElemToList(List *list, char palavra[TAM_PAL], char significado[TAM_SIG]) {
  no *newNode = NULL;
  if(list->inicio == NULL) {
    newNode = (no *) malloc(sizeof(no));
    if(!newNode)
      return -1;
    strncpy(newNode->palavra, palavra, TAM_PAL);
    strncpy(newNode->significado, significado, TAM_SIG);
    newNode->prox = NULL;

    (list->tam)++;
    list->inicio = newNode;
    return 0;
  }
  no *aux_node = list->inicio;
  while(aux_node->prox != NULL && strncmp(palavra, aux_node->prox->palavra, TAM_PAL) < 0) {
    aux_node = aux_node->prox;
  }

  if(strncmp(palavra, aux_node->palavra, TAM_PAL) == 0)
    return 1;

  newNode = (no *) malloc(sizeof(no));
  if(!newNode)
    return -1;

  strncpy(newNode->palavra, palavra, TAM_PAL);
  strncpy(newNode->significado, significado, TAM_SIG);
  newNode->prox = aux_node->prox;
  aux_node->prox = newNode;

  (list->tam)++;
  return 0;
}

no *buscaList(List *list, char palavra[TAM_PAL]) {
  if(list->tam == 0)
    return NULL;

  no *aux_node = list->inicio;
  while(aux_node && strncmp(palavra, aux_node->palavra, TAM_PAL) < 0)
    aux_node = aux_node->prox;

  if(strncmp(palavra, aux_node->palavra, TAM_PAL) == 0)
    return aux_node;

  return NULL;
}

void destroiList(List *list) {
  no *aux_node = list->inicio;
  if(!aux_node)
    return;

  no *prox = aux_node->prox;

  while(prox) {
    free(aux_node);
    aux_node = prox;
    prox = prox->prox;
  }
  free(aux_node);
}
