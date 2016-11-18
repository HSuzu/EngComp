#ifndef HASH_H
#define HASH_H

#include "list.h"

#define NUM_ENT 500

typedef struct _hash {
  List entrada[NUM_ENT];
  int num_clsn; // numero se colisões
} Hash;

void criaHash(Hash *h);
unsigned int hash(char in[TAM_PAL]);
int addElemToHash(Hash *h, char palavra[TAM_PAL], char significado[TAM_SIG]);
int buscaSignHash(Hash *h, char palavra[TAM_PAL], char out[TAM_SIG]);
int maxtamList(Hash *h);
void destroiHash(Hash *h);

#endif
