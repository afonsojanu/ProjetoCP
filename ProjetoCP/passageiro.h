#ifndef H_PASSAGEIRO
#define H_PASSAGEIRO
#include "cartao.h"


typedef struct _passageiro {
  char *email;
  char *nome;
} passageiro;

// Aqui uso um duplo apontador que vai ser um apontador para uma alocação dinamica de arrays;
typedef struct _listaPassageiro {
  passageiro **passengers;
  int size;
  int capacity;
} listaPassageiros;

// Prototipos
listaPassageiros *criaListaPassageiros(int capacity);
void adicionaPassageiro(listaPassageiros *list, passageiro *passenger);
void destroiListaPassageiros(listaPassageiros *list);
void mostraPassageiro(listaPassageiros *list, listaCartoes *listaC);
int verificarPassageiro(listaPassageiros *list, char *email);
passageiro *encontraPassageiroPorEmail(listaPassageiros *lista, char *email);

#endif