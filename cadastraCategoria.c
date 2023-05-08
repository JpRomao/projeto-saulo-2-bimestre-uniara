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

int cadastraCategoria()
{
  int categoria;

  printf("Digite a qual categoria o funcionario sera classificado\n 1- Gerencia\n 2- Supervisao\n 3- Operacional\n R:  ");
  scanf("%d", &categoria);
  switch (categoria)
  {
  case 1:
    printf("\nVoce cadastrou um funcionario no setor de Gerencia");
    break;
  case 2:
    printf("\nVoce cadastrou um funcionario no setor de Supervisao");
    break;
  case 3:
    printf("\nVoce cadastrou um funcionario no setor Operacional");
    break;
  }
  return categoria;
}

int main()
{
  int categoria = cadastraCategoria();
  printf(" - Categoria: %d\n", categoria);

  return 0;
}
