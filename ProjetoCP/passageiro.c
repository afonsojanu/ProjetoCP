#include "passageiro.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Cria uma nova lista de passageiros dada uma capacidade inicial;
 * Retorna um apontador para a nova lista se tudo correr bem, ou NULL se a alocação de memoria falhar;
 */
listaPassageiros *criaListaPassageiros(int capacity) {
  listaPassageiros *list = (listaPassageiros *)malloc(sizeof(listaPassageiros));
  if (list == NULL) {
    return NULL;
  }
  list->passengers = (passageiro **)malloc(capacity * sizeof(passageiro *));
  if (list->passengers != NULL) {
    list->size = 0;
    list->capacity = capacity;
  } else {
    free(list);
    return NULL;
  }
  return list;
}

/**
 * Destroi a lista de passageiros libertando a memoria reservada bem como a memoria de cada elemento da lista;
 */
void destroiListaPassageiros(listaPassageiros *list) {
  for (int i = 0; i < list->size; i++) {
    free(list->passengers[i]->nome);
    free(list->passengers[i]);
  }
  free(list->passengers);
  free(list);
}

/**
 * Adiciona um novo passageiro a lista
 * Se a lista tiver na sua capacidade maxima impede de adicionar;
 */
void adicionaPassageiro(listaPassageiros *list, passageiro *passenger) {
  if (list->size == list->capacity) {
    printf("a lista esta cheia");
  }else{
    list->passengers[list->size++] = passenger;
  }
  
}

/**
 * Lista todos os elementos da lista;
 */
void mostraPassageiro(listaPassageiros *list, listaCartoes *listC) {
  printf("Lista de Passageiros:\n");
  for (int i = 0; i < list->size; i++) {
    printf("Nome do passageiro:%s, Email do passageiro(%s)\nUltima localidade da estação:%s, Pontos que o passageiro tem no cartão (%d)\n", list->passengers[i]->nome, list->passengers[i]->email,listC->cartoes[i]->destino,listC->cartoes[i]->pontos);
  }
  sleep(2);
  criaMenu();
}

/**
 * Vai verificar se existe algum passageiro com x email;
 */

int verificarPassageiro(listaPassageiros *list, char *email){
  for (int i = 0; i < list->size; i++) {
      if(!strcmp(list->passengers[i]->email, email)){
        return 1;
      }
  }

  return 0;
}
/**
 * Encontra um passageiro na lista pelo email;
 */
passageiro *encontraPassageiroPorEmail(listaPassageiros *lista, char *email) {
  // Vai verificar se a lista é nula ou vazia
  if (lista == NULL || lista->size == 0) {
    return NULL;
  }

  // Percorre a lista e compara o email de cada passageiro com o email passado como parâmetro;
  for (int i = 0; i < lista->size; i++) {
    if (strcmp(lista->passengers[i]->email, email) == 0) {
      return lista->passengers[i];
    }
  }

  // O passageiro não foi encontrado;
  return NULL;
}