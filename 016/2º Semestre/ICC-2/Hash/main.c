#include"lib/hash.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char const *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Insira apos %s o caminho para o dicionario\n", argv[0]);
    return -1;
  }

  fprintf(stdout, "Arquivo: %s\n", argv[1]);

  FILE *fd = fopen(argv[1], "r");
  if(!fd) {
    fprintf(stderr, "Erro ao abrir o arquivo %s\n", argv[1]);
    return -2;
  }

  fprintf(stdout, "Arquivo aberto com sucesso!\n");

  Hash h;
  criaHash(&h);

  char palavra[TAM_PAL];
  char significado[TAM_SIG];

  while( fgets(palavra, TAM_PAL, fd) &&  fgets(significado, TAM_SIG, fd) ) {
    if(significado[0] == '\n') // problema com palavras de 8 letras...
      fgets(significado, TAM_SIG, fd);
    addElemToHash(&h, palavra, significado);
  }

  fprintf(stdout, "Arquivo lido com sucesso.\nColisoes: %d\nTamanho maximo de lista: %d\n", h.num_clsn, maxtamList(&h));
  fprintf(stdout, "Digite a palavra a ser buscada ou 'quit' para sair\n");

  while(fgets(palavra, TAM_PAL, stdin) != NULL && (strncmp(palavra, "quit", 4) != 0)) {
    if(palavra[0] != '\n') { // problema com 8 letras
      if( buscaSignHash(&h, palavra, significado)  < 0 ) {
        fprintf(stderr, "Palavra nao encontrada\n");
      }
      fprintf(stdout, "%s\n", significado);
    }
  }
  fclose(fd);
  destroiHash(&h);
  return 0;
}
