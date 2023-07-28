#include "estacao.h"
#include "passageiro.h"
#include "menu.h"
#include "cartao.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

//Função que vai fazer a verificação para ver se um email é válido;
int validacaoemail(char *email) {
  regex_t regex;
  int reti = regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
  if (reti) {
    printf("Erro ao compilar expressão regular para validação de email.\n");
    return 0;
  }
  reti = regexec(&regex, email, 0, NULL, 0);
  if (!reti) {
    return 1;
  } else if (reti == REG_NOMATCH) {
    printf("Email inválido. Por favor, insira um email válido.\n");
    return 0;
  } else {
    printf("Erro ao executar expressão regular para validação de email.\n");
    return 0;
  }
}
////Função que vai verificar se o nome é valido;
int validacaonome(char *name) {
  int i = 0;
  while (name[i] != '\0') {
    if (!isalpha(name[i]) && !isspace(name[i])) {
      printf("Nome é inválido. Por favor, insira um nome válido.\n");
      return 0;
    }
    i++;
  }
  return 1;
}
//Funçao que vai adicionar passageiros na lista;
void executaAdicionaPassageiro(listaPassageiros *lista, listaCartoes *listaC) {
 
  passageiro *passenger = (passageiro *)malloc(sizeof(passageiro));
  cartao *card = malloc(sizeof(cartao));

  do {
    printf("\nEmail:");
    scanf("%ms", &(passenger->email));
  } while (!validacaoemail(passenger->email) || encontraPassageiroPorEmail(lista, passenger->email) != NULL);

  do {
    printf("\nNome:");
    scanf("%ms", &(passenger->nome));
  } while (!validacaonome(passenger->nome));

  card->email = passenger->email;
  card->destino = "";
  card->pontos = 1;

  adicionaPassageiro(lista, passenger);
  adicionaCartao(listaC, card);

  printf("Passageiro foi criado com sucesso!\n");
  sleep(2);
  criaMenu();
}

//Funçao que vai adicionar as estações;
void executaAdicionaEstacao(listaEstacoes *lista) {
  estacao *estacao = malloc(sizeof(estacao));
  char nome[50];
  int id = rand() % 200;

  printf("\nNome:");

  scanf(" %ms", &(estacao->nome));

  printf("\nLocalidade:");
  scanf("%ms", &(estacao->localidade));

  if (verificarEstacao(lista, id) == 0) {
    estacao->codEstacao = id;
  } else {
    printf("Codigo de Estacao ja foi registado anteriormente.");                                               
    return;                                             
  }

  printf("\nStock de Brindes:");
  scanf("%d", &(estacao->stockBrindes));

  estacao->brindesLocalidade = 0;
  
  adicionaEstacao(lista, estacao);

  printf("Estacao criada com sucesso!\n");
  sleep(2);
  criaMenu();
}

//Funçao que vai incrementar brindes;
void executaIncrementaBrinde(listaEstacoes *lista) {
  estacao *estacao = malloc(sizeof(estacao));
  int quantia, id;

 

  printf("\nCodigo da Estacao:");
  scanf("%d", &id);

  printf("\nQuantia de Brindes a adicionar:");
  scanf("%d", &quantia);

  if (verificarEstacao(lista, id) == 1) {
    incrementaBrindes(lista, id, quantia);
    printf("Atualizacao de brindes bem sucedida.\n");
    sleep(2);
    criaMenu();
  } else {
    printf("Estacao desconhecida.");
    printf("\n O que pretende fazer? ");
  }
}

//Funçao que vai fazer o registo de viagem;
void executaAdicionaViagem(listaCartoes *listaC, listaPassageiros *listaP,listaEstacoes *listaE) {
  char *email;
  int id, pontos;

  printf("\nEmail:");
  scanf("%ms", &email);

  if (verificarPassageiro(listaP, email) == 1) {
    printf("\nCodigo da Estacao:");
    scanf("%d", &id);

    pontos = (rand() % 5) + 1;

    if (verificarEstacao(listaE, id) == 1) {
      char *destino = encontraNomeEstacao(listaE, id);
      adicionaViagem(listaC, email, destino, pontos);
      printf("Registo de viagem bem sucedido.\n");
      sleep(2);
      criaMenu();
    } else {
      printf("Estacao desconhecida.\n");
      sleep(2);
      criaMenu();
    }
  } else {
    printf("Passageiro desconhecido.\n");
    sleep(2);
    criaMenu();
  }
}

//Funçao que vai permitir que o utilizador escolha o numero de brindes;
void executaEscolherBrindes(listaCartoes *listaCrt, listaPassageiros *listaPassa, listaEstacoes *listaEst) {
  char *email;
  int id, pontos;

  printf("\nEmail:");
  scanf("%ms", &email);

  if (verificarPassageiro(listaPassa, email) == 1) {
    printf("\nCodigo da Estacao:");
    scanf("%d", &id);

    if (verificarEstacao(listaEst, id) == 1) {
      printf("\nEscolha o número de brindes:");
      scanf("%d", &pontos);
      if (verificarBrindes(listaEst, id, pontos) == 1) {
        if (verificarPontos(listaCrt, email, pontos) == 1) {
          escolhaBrindes(listaCrt, email, pontos);
          removerBrindes(listaEst, id, pontos);
          incrementaBrindeLocalidade(listaEst, id, pontos);
          printf("Escolha de brindes efetuada.\n");
          sleep(2);
          criaMenu();
        } else {
          printf("Quantidade insuficiente de pontos no cartao.\n");
          sleep(2);
          criaMenu();
        }
      } else {
        printf("Quantidade indisponivel de brindes na estacao.\n");
        sleep(2);
        criaMenu();
      }
    } else {
      printf("Estacao desconhecida.\n");
      sleep(2);
      criaMenu();
    }

  } else {
    printf("Passageiro desconhecido.\n");
    sleep(2);
    criaMenu();
  }
}

//Funçao que mostra o top brindes consoante a localidade;
void executaTopBrindes(listaEstacoes *lista) {
  if(lista->size > 0){
    if(verificarBrindesLocalidade(lista) == 1){
      topBrindesF(lista);
    }else{
       printf("Ainda não foram distribuidos quaisquer brindes.\n");
      sleep(2);
      criaMenu();
    }
    
  }else{
    printf("Nao existem estacoes registadas.\n");
    sleep(2);
    criaMenu();
  }
}

int main(void) {
  char comando[2];
  listaPassageiros *listaPassageiros = criaListaPassageiros(100);
  listaEstacoes *listaEstacoes = criaListaEstacoes(100);
  listaCartoes *listaCartoes = criaListaCartoes(100);


  // COMANDOS;
  char saida[] = "S";
  char help[] = "A";
  char registaPassageiro[] = "RP";
  char registaEstacao[] = "RE";
  char registaViagem[] = "RV";
  char incrementaBrindes[] = "IB";
  char escolhaBrindes[] = "EB";
  char topBrindes[] = "TB";
  char consultaEstacao[] = "CE";
  char listaPassagerio[] = "LP";

  criaMenu();

  while (strcmp(comando, saida) != 0) {
    scanf(" %s", comando);

    if (!strcmp(registaPassageiro, comando)) {
       executaAdicionaPassageiro(listaPassageiros, listaCartoes);
    }

    else if (!strcmp(listaPassagerio, comando)) {
       mostraPassageiro(listaPassageiros, listaCartoes);
    }

    else if (!strcmp(registaEstacao, comando)) {
      executaAdicionaEstacao(listaEstacoes);
    }

    else if (!strcmp(consultaEstacao, comando)) {
      mostraEstacoes(listaEstacoes);
    }

    else if (!strcmp(escolhaBrindes, comando)) {
      executaEscolherBrindes(listaCartoes, listaPassageiros, listaEstacoes);
    }

    else if (!strcmp(incrementaBrindes, comando)) {
      executaIncrementaBrinde(listaEstacoes);;
    }

    else if (!strcmp(topBrindes, comando)) {
       executaTopBrindes(listaEstacoes);
    }

    else if (!strcmp(registaViagem, comando)) {
       executaAdicionaViagem(listaCartoes, listaPassageiros, listaEstacoes);
    }

    else if (!strcmp(help, comando)) {
      criaMenu();
    } else {
      printf("----\n Comando invalido! \n----\n\n\n");
    }
  }
}