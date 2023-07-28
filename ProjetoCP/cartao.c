#include "cartao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Criar uma nova lista de cartoes
 * Retorna um apontador para a nova lista se tudo correr bem, ou NULL se a alocacao de memoria falhar
 */
listaCartoes *criaListaCartoes(int capacity) {
  listaCartoes *list = (listaCartoes *)malloc(sizeof(listaCartoes));
  if (list == NULL) {
    return NULL;
  }
  list->cartoes = (cartao **)malloc(capacity * sizeof(cartao *));
  if (list->cartoes != NULL) {
    list->size = 0;
    list->capacity = capacity;
  } else {
    free(list);
    return NULL;
  }
  return list;
}

/**
 * Destroi a lista de cartoes libertando a memoria reservada bem como a memoria de cada elemento da lista
 */
void destroiListaCartoes(listaCartoes *list) {
  for (int i = 0; i < list->size; i++) {
    free(list->cartoes[i]->email);
    free(list->cartoes[i]);
  }
  free(list->cartoes);
  free(list);
}


/**
 * Adiciona um novo cartao a lista
 * Se a lista tiver uma capacidade maxima impede de adicionar
 */
void adicionaCartao(listaCartoes *list, cartao *cartao) {
  if (list->size == list->capacity) {
    printf("a lista está cheia");
  } else {
    list->cartoes[list->size++] = cartao;
  }
}

/**
 * Adiciona uma nova viagem ao cartao
 * Se a lista tiver uma capacidade maxima impede de adicionar
 */

int adicionaViagem(listaCartoes *list, char *email, char *destino, int pontos) {
  for (int i = 0; i < list->size; i++) {
    if (!strcmp(list->cartoes[i]->email, email)) {
      list->cartoes[i]->destino = destino;
      list->cartoes[i]->pontos += pontos;

      return 1;
    }
  }

  return 0;
}

/**
 * Escolha de brindes, remove pontos do cartão consoante a escolha do utilizador
 */
void escolhaBrindes(listaCartoes *list, char *email, int pontos) {
   for (int i = 0; i < list->size; i++) {
      if(!strcmp(list->cartoes[i]->email, email)){
        list->cartoes[i]->pontos = list->cartoes[i]->pontos - pontos;    
        return;
      }
  }
}

/**
 * Verifica se o passageiro tem pontos suficientes
 */
int verificarPontos(listaCartoes *list, char *email, int pontos) {
   for (int i = 0; i < list->size; i++) {
      if(list->cartoes[i]->pontos > pontos){ 
        return 1;
      }else{
        return 0;
      }
  }
  return 0;
}