#ifndef H_CARTAO
#define H_CARTAO

typedef struct _cartao {
  char *email;
  char *destino;
  int pontos;
} cartao;

typedef struct _listaCartoes {
  cartao **cartoes;
  int size;
  int capacity;
} listaCartoes;

//Prototipos
listaCartoes *criaListaCartoes(int capacity);
void adicionaCartao(listaCartoes *list, cartao *cartao);
void destroiListaCartoes(listaCartoes *list);
int adicionaViagem(listaCartoes *list, char *email, char *destino, int pontos);
void escolhaBrindes(listaCartoes *list, char *email, int pontos);
int verificarPontos(listaCartoes *list, char *email, int pontos);

#endif