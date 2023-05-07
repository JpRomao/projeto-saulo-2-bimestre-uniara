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

int main()
{
  char nome[20] = "";
  strcpy(nome, cadastraNome());
  int idade = cadastraIdade();
  double salario = cadastraSalario();

  printf("nome:%s\n", nome);
  printf("idade:%d\n", idade);
  printf("salario:%lf\n", salario);

  return 0;
}