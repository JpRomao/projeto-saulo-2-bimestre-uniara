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

void limparBuffer()
{
  while (getchar() != '\n' && getchar() != '\r')
  {
  }
}

void limparFgets(char *string)
{
  string[strcspn(string, "\r\n")] = '\0';
}

char *cadastraNome()
{

  char *nome = malloc(20 * sizeof(char));

  printf("Digite o nome do funcionario: ");
  fgets(nome, 20, stdin);
  limparFgets(nome);

  return nome;
}

int cadastraIdade()
{
  int idade;

  do
  {
    printf("Digite a idade do funcionario: ");
    scanf("%d", &idade);
    limparBuffer();

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
  limparBuffer();

  return salario;
}

int cadastraCategoria()
{
  int categoria;

  printf("Digite a qual categoria o funcionario sera classificado\n 1- Gerencia\n 2- Supervisao\n 3- Operacional\n R:  ");
  scanf("%d", &categoria);
  limparBuffer();

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

char *nomeCategoria(int categoria)
{
  switch (categoria)
  {
  case 1:
    return "Gerencia";

  case 2:
    return "Supervisao";

  case 3:
    return "Operacional";

  default:
    return "invalida";
  }
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

double Maior_Salario(double a, double b)
{
  double maior;
  if (a > b)
  {
    maior = a;
  }
  else
  {
    maior = b;
  }
  return maior;
}

double Menor_Salario(double a, double b)
{
  double menor;
  if (a < b)
  {
    menor = a;
  }
  else
  {
    menor = b;
  }
  return menor;
}

int main()
{
  Reg funcionario = criarFuncionario();

  printf("\n--------- Funcionario Cadastrado ----------\n");
  printf("Nome: %s\n", funcionario.nome);
  printf("Categoria: %s\n", nomeCategoria(funcionario.categoria));
  printf("Salario: %.2lf\n", funcionario.salario);
  printf("Idade: %d\n", funcionario.idade);

  return 0;
}
