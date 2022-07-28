#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nome[50];
  char endereco[50];
  char telefone[10];
  int cpf;
  float saldo;
} Cliente;

typedef struct {
  int capacidade;
  Cliente *dados;
  int ultimo;
} Lista;

void criarLista (Lista * l, int c) {
  l -> capacidade = c;
  l -> dados = (Cliente*) malloc (l -> capacidade * sizeof(Cliente));
  l -> ultimo = -1;
}

int buscaCadastro (Lista * l, int cpf) {
  for (int i = 0; i < l -> ultimo + 1; i++) {
    if (l -> dados[i].cpf == cpf) {
      printf ("\nCliente encontrado.");
      return i;
      break;
    }
    else {
      printf ("\nCliente não encontrado.\n");
      return -1;
    }
  }
}

int retirarSaldo (Lista * l, int cpf, int valor) {
  int cadastro;
  cadastro = buscaCadastro(l, cpf);
  if (cadastro == -1) {
    return -1;
  }
  else {
    if (l -> dados[cadastro].saldo >= valor) {
      l -> dados[cadastro].saldo -= valor;
      printf ("Retirada feita com sucesso!\n");
    }
    else {
      printf ("Não foi possível fazer a retirada. Valor excede o saldo!\n");
      return -2;
    }
  }
}

int inserirCliente (Lista * l, Cliente novo) {
  if (l -> ultimo >= l -> capacidade - 1) { //verifica se a lista está cheia
    printf ("\nNão foi possível inserir um novo cliente. Não há espaço!\n");
    return -1;
  }
  else {
    l -> ultimo++;
    l -> dados[l -> ultimo] = novo;
    printf ("Cliente inserido com sucesso!\n");
    return 0;
  }
}

int retirarCliente (Lista * l, int cpf) {
  int removido, i = 0;
  removido = buscaCadastro(l, cpf);
  if (removido == -1) {
    printf ("Impossível remover. Cliente não encontrado no sistema.\n");
    return -1;
  }
  else {
    for (i = removido; i < l -> ultimo - 1; i++) {
      l -> dados[i] = l -> dados[i+1];	
      l -> ultimo-- ;
      printf ("Cliente removido com sucesso!\n");
      return 0;     
    }
  }
}

void main () {

  int opcao, cpf;
  float valor;

  Lista *clientes = (Lista*) malloc (sizeof(Lista));
  int capacidade;
  Cliente novoCliente;

  printf ("\n Insira a capacidade da lista: ");
  scanf ("%d", &capacidade);

  criarLista(clientes, capacidade);

  do {

    printf ("\n---- Banco DEIXE SEU DINHEIRO COMIGO ----\n");
    printf ("Escolha o que deseja fazer: ");
    printf ("\n[1] Verificar cadastro\n[2] Retirada de saldo\n[3] Inserir novo cliente\n[4] Remover cliente\n[5] Sair\n");

    printf ("\nDigite a opção desejada: ");
    scanf ("%d", &opcao);

    switch (opcao)
  {
  case 1:
    printf ("\nDigite o CPF do dono do cadastro: ");
    scanf ("%d", &cpf);
    buscaCadastro(clientes, cpf);
    break;
  
  case 2:
    printf ("\nDigite o CPF do dono da conta: ");
    scanf ("%d", &cpf);
    printf ("\nDigite o valor a ser retirado: ");
    scanf ("%f", &valor);
    retirarSaldo(clientes, cpf, valor);
    break;

  case 3:
    printf ("\nNome: ");
    fflush(stdin);
    gets (clientes -> dados[clientes -> ultimo].nome);
    printf ("\nEndereço: ");
    fflush(stdin);
    gets (clientes -> dados[clientes -> ultimo].endereco);
    printf ("\nTelefone: ");
    fflush(stdin);
    gets (clientes -> dados[clientes -> ultimo].telefone);
    printf ("\nCPF: ");
    scanf ("%d", &clientes -> dados[clientes -> ultimo].cpf);
    printf ("\nSaldo: ");
    scanf ("%f", &clientes -> dados[clientes -> ultimo].saldo);
    inserirCliente(clientes, novoCliente);
    break;

  case 4:
    printf ("\nDigite o CPF do cliente que deseja remover: ");
    scanf ("%d", &cpf);
    retirarCliente(clientes, cpf);
    break;

  case 5:
    printf ("\nObrigado por usar os nossos serviços!");
    break;

  default:
    printf ("\nEssa opção não existe.");
    break;
  }
  } while (opcao != 5);

}