#include "CyclicList.h"
#include <stdio.h>
#include <stdlib.h>

void createList(List *l, int *err) {
  Node *head = (Node *)malloc(sizeof(Node));
  head->next = head;

  l->head   = head;
  l->tail   = head;
  l->length = 0;
}

int isEmptyList(List *l) {
  if(l->length > 0) return 0;
  return 1;
}

int insertElemAt(List *l, elem e, int pos, int *err) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  if(!newNode) {
    *err = -1;
    return -1;
  }

  newNode->info = e;
/*
  if( !(l->first) ) { // não há elementos na lista
    l->first      = newNode;
    l->last       = newNode;
    newNode->next = newNode;

    (l->length)++;
    *err = 0;
    return 0;
  }

// insere no início
  if(pos == 0) {
    newNode->next = l->first;
    l->first      = newNode;

    (l->length)++;
    *err = 0;
    return 0;
  }
// insere no final
  if(pos < 0) {
    newNode->next = l->first;
    l->last->next = newNode;

    (l->length)++;
    *err = 0;
    return 0;
  }
// insere no meio
*/

// insere no final
  if(pos < 0) {
    newNode->next = l->head;
    l->tail->next = newNode;

    (l->length)++;
    *err = 0;
    return 0;
  }


  Node *prev, *current;
  prev = l->tail;
  current = l->head;

  if(pos > l->length) pos %= l->length;

  int i = 0;
  while(i++ < pos) {
    prev = current;
    current = current->next;
  }

  prev->next = newNode;
  newNode->next = current;

  *err = 0;

  return pos;
}

void removeElement(List *l, elem *x, int *err) {
  if(isEmptyList(l)) {
    *err = -1;
    return;
  }

  int len = 0;
  Node *prev = l->last;
  Node *current = l->first;
  while(len < l->length && current->info == *x) {
    prev    = current;
    current = current->next;
    len++;
  }

  if(len >= l->length) { // elemento não encontrado
    *err = 1;
    return;
  }

  if(len == 0) { // primeiro elemento
    l->first = current->next;
    l->last->next = l->first;
    free(current);

    goto success;
  }

  if(len == l->length - 1) { // último elemento
    l->last = prev;
    prev->next = l->first;
    free(current);

    goto success;
  }

// elemento do meio
  prev->next = current->next;
  free(current);

success:
  (l->length)--;
  *err = 0;
  return;
}

void removeElemAt(List *l, elem e, int pos, int *err) {
  if(isEmptyList(l)) {
    *err = -1;
    return;
  }

  Node *aux = NULL;

  if(pos == 0) {
    aux = l->first;
    l->first = aux->next;
  }

}
