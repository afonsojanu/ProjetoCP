#include "estacao.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Cria uma nova lista de estacoes dada uam capacidade inicial;
 * Retorna um apontador para a nova lista se tudo correr bem, ou NULL se a alocacao de memoria falhar;
 */
listaEstacoes *criaListaEstacoes(int capacity) {
  listaEstacoes *list = (listaEstacoes *)malloc(sizeof(listaEstacoes));
  if (list == NULL) {
    return NULL;
  }
  list->estacoes = (estacao **)malloc(capacity * sizeof(estacao *));
  if (list->estacoes != NULL) {
    list->size = 0;
    list->capacity = capacity;
  } else {
    free(list);
    return NULL;
  }
  return list;
}

/**
 * Vai destruir a lista de estações libertando a memoria reservada bem como a memoria de cada elemento da lista;
 */
void destroiListaEstacoes(listaEstacoes *list) {
  for (int i = 0; i < list->size; i++) {
    free(list->estacoes[i]->nome);
    free(list->estacoes[i]);
  }
  free(list->estacoes);
  free(list);
}

/**
 * Vai adicionar uma nova estação a lista;
 * Se a lista tiver uma capacidade maxima impede de adicionar;
 */
void adicionaEstacao(listaEstacoes *list, estacao *estacao) {
  if (list->size == list->capacity) {
    printf("a lista está cheia");
  } else {
    list->estacoes[list->size++] = estacao;
  }
}

/**
 * Lista todos os elementos da lista;
 */
void mostraEstacoes(listaEstacoes *list) {
  printf("\n\nLista de estações\n");
  for (int i = 0; i < list->size; i++) {
    printf("Codigo da Estação(%d)\nLocalidade(%s) - (%s)\nNúmero de stock de brinde(%d)\n\n",list->estacoes[i]->codEstacao,list->estacoes[i]->localidade,list->estacoes[i]->nome ,list->estacoes[i]->stockBrindes);
  }
  sleep(2);
  criaMenu();
}

/**
  * Incrementa n valor no stock de "x" estacao;
*/
void incrementaBrindes(listaEstacoes *list, int id, int quantia){
  for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->codEstacao == id){
        list->estacoes[i]->stockBrindes += quantia;
      }
  }
}

/**
  * Verifica se o existe alguma estacao com o id inserido;
*/
int verificarEstacao(listaEstacoes *list, int id){
  for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->codEstacao == id){
        return 1;
      }
  }

  return 0;
}

/**
  * Encontra o nome da estação pelo código da estação inserida pelo utilizador;
*/
char* encontraNomeEstacao(listaEstacoes *list, int id){
  for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->codEstacao == id){
        char *destino;
        destino = list->estacoes[i]->localidade;       
        return destino;
      }
  }

  return "";
}

/**
 * Verifica se a estacao tem brindes suficientes;
 */
int verificarBrindes(listaEstacoes *list, int id, int pontos) {
   for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->stockBrindes > pontos){ 
        return 1;
      }else{
        return 0;
      }
  }
  return 0;
}

/**
 * Vai remover o numero de brindes que o passageiro escolheu;
 */
void removerBrindes(listaEstacoes *list, int id, int pontos) {
   for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->codEstacao == id){ 
        list->estacoes[i]->stockBrindes -= pontos;
        return;
      }
  }
}

/**
 * Vai imprimir na linha de comandos o top de estacoes com maior número de brindes;
 */
void topBrindesF(listaEstacoes *list) {
  int i, j;
  for (i = 0; i < list->size - 1; i++) {
    for (j = 0; j < list->size - i - 1; j++) {
      if (list->estacoes[j]->brindesLocalidade < list->estacoes[j + 1]->brindesLocalidade) {
        estacao *temp = list->estacoes[j];
        list->estacoes[j] = list->estacoes[j + 1];
        list->estacoes[j + 1] = temp;
      }
    }
  }

  for(i = 0; i < list->size; i++) {
    printf("%d - %s (%d)\n", i+1, list->estacoes[i]->localidade, list->estacoes[i]->brindesLocalidade);
  }
}

/**
 * Vai incrementar n valor no campo brindesDistri de x estacao;
 */
void incrementaBrindeLocalidade(listaEstacoes *list, int id, int quantia){
  for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->codEstacao == id){
        list->estacoes[i]->brindesLocalidade += quantia;
      }
  }
}

/**
 * Vai verificar se houve uma distribuicao de brindes;
 */
int verificarBrindesLocalidade(listaEstacoes *list) {
   for (int i = 0; i < list->size; i++) {
      if(list->estacoes[i]->brindesLocalidade > 0){ 
        return 1;
      }
   }
  return 0;
}