#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Funcionario
{
  char nome[20];
  double salario;
  int categoria;
  int idade;
} Reg;

char *cadastraNome()
{

  char *nome = malloc(20 * sizeof(char));

  printf("Digite o nome do funcionario: ");
  fgets(nome, 20, stdin);
  nome[strcspn(nome, "\r\n")] = 0;

  return nome;
}

int cadastraIdade()
{
  int idade;

  do
  {
    printf("Digite a idade do funcionario: ");
    scanf("%d", &idade);

    if (idade <= 0)
    {
      printf("A idade digitada eh invalida! Digite novamente.\n");
    }
  } while (idade <= 0);
  return idade;
}

double cadastraSalario()
{
  double salario;

  printf("Digite o salario do funcionario: ");
  scanf("%lf", &salario);

  return salario;
}

int cadastraCategoria()
{
  int categoria;

  printf("Digite a qual categoria o funcionario sera classificado\n 1- Gerencia\n 2- Supervisao\n 3- Operacional\n R:  ");
  scanf("%d", &categoria);
  switch (categoria)
  {
  case 1:
    printf("\nVoce cadastrou um funcionario no setor de Gerencia.\n");
    break;
  case 2:
    printf("\nVoce cadastrou um funcionario no setor de Supervisao.\n");
    break;
  case 3:
    printf("\nVoce cadastrou um funcionario no setor Operacional.\n");
    break;
  }
  return categoria;
}

Reg criarFuncionario()
{
  Reg funcionario;

  strcpy(funcionario.nome, cadastraNome());
  funcionario.categoria = cadastraCategoria();
  funcionario.salario = cadastraSalario();
  funcionario.idade = cadastraIdade();

  printf("Funcionario criado com sucesso!\n");

  return funcionario;
}

int main()
{
  Reg funcionario = criarFuncionario();

  printf("\n--------- Funcionario Cadastrado ----------\n");
  printf("Nome: %s\n", funcionario.nome);
  printf("Categoria: %d\n", funcionario.categoria);
  printf("Salario: %.2lf\n", funcionario.salario);
  printf("Idade: %d\n", funcionario.idade);

  return 0;
}
