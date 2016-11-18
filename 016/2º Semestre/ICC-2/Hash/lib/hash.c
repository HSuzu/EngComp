#include"hash.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int primos[8] = {2,3,5,7,11,13,17,19};

void criaHash(Hash *h) {
  int i;
  for( i = 0; i < NUM_ENT; i++ ) {
    criaList(&(h->entrada[i]));
  }
  h->num_clsn = 0;
}

unsigned int hash(char in[TAM_PAL]) {
  unsigned int sum = 0;
  unsigned int i = 0;
  while(i < TAM_PAL && in[i] != '\0') {
    sum = sum + primos[i] * in[i];
    i++;
  }
  return sum%NUM_ENT;
}

int addElemToHash(Hash *h, char palavra[TAM_PAL], char significado[TAM_SIG]) {
  int idx = hash(palavra);
  printf("%d\n", idx);
  int returnValue = addElemToList(&(h->entrada[idx]), palavra, significado);
  if( returnValue == 0 && h->entrada[idx].tam > 1 ) {
    (h->num_clsn)++;
  }

  return returnValue;
}

int buscaSignHash(Hash *h, char palavra[TAM_PAL], char out[TAM_SIG]) {
  int idx = hash(palavra);

  no *aux = buscaList(&(h->entrada[idx]), palavra);
  if(aux) {
    strncpy(out, aux->significado, TAM_SIG);
    return 0;
  }
  out[0] = '\0';
  return -1;
}

int maxtamList(Hash *h) {
  int i, tam = 0;
  for( i = 0; i < NUM_ENT; i++ ) {
    if(h->entrada[i].tam > tam) {
      tam = h->entrada[i].tam;
    }
  }
  return tam;
}

void destroiHash(Hash *h) {
  int i;
  for( i = 0; i < NUM_ENT; i++ ) {
    destroiList(&(h->entrada[i]));
  }
}
