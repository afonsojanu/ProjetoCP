#ifndef H_ESTACAO
#define H_ESTACAO

typedef struct _estacao {
  char *nome;
  char *localidade;
  int codEstacao;
  int stockBrindes;
  int brindesLocalidade;
} estacao;

typedef struct _listaEstacoes {
  estacao **estacoes;
  int size;
  int capacity;
} listaEstacoes;

// Prototipos
listaEstacoes *criaListaEstacoes(int capacity);
void adicionaEstacao(listaEstacoes *list, estacao *estacao);
void destroiListaEstacoes(listaEstacoes *list);
void mostraEstacoes(listaEstacoes *list);
void incrementaBrindes(listaEstacoes *list, int id, int quantia);
int verificarEstacao(listaEstacoes *list, int id);
char *encontraNomeEstacao(listaEstacoes *list, int id);
int verificarBrindes(listaEstacoes *list, int id, int pontos);
void removerBrindes(listaEstacoes *list, int id, int pontos);
void topBrindesF(listaEstacoes *list);
void incrementaBrindeLocalidade(listaEstacoes *list, int id, int quantia);
int verificarBrindesLocalidade(listaEstacoes *list);

#endif
