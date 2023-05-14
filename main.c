#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** VARIÁVIES DE TESTE */

// Mudar para 'PROD' para rodar em producao e 'TEST' para rodar em testes
#define AMBIENTE 'TEST'
// Mudar esta variável irá resultar na mudança da quantidade de funcionários gerados aleatoriamente
#define GERAR_FUNCIONARIOS_ALEATORIOS 3

/***/

// Mudar esse numero irá resultar na mudança da quantidade de funcionarios listados por pagina
#define LIMITE_LISTAGEM 1

typedef struct Funcionario
{
  int id;
  char nome[20];
  double salario;
  int categoria;
  int idade;
} Reg;

int quantidadeFuncionarios = 0;

void limparBuffer();
void limparFgets(char *string);
void gerarFuncionariosAleatorios(Reg *funcionarios);
void menuPrincipal(Reg *funcionarios);
void informacoesFuncionario();
void listarFuncionarios(Reg *funcionarios, int pagina, int final);
void mostrarFuncionario(Reg funcionario);
void menu();
int numeroFuncionariosRegistrados(Reg *funcionarios);
int gerarId();
int cadastraIdade();
int cadastraCategoria();
char *cadastraNome();
char *nomeCategoria(int categoria);
double cadastraSalario();
Reg adicionarFuncionario(Reg *funcionarios, Reg novoFuncionario);
Reg criarFuncionario();
Reg criarFuncionarioAleatorio(Reg *funcionarios);

int main()
{
  Reg *funcionarios = malloc(1 * sizeof(Reg));

  if (AMBIENTE == 'TEST')
  {
    gerarTresFuncionariosAleatorios(funcionarios);
  }

  menuPrincipal(funcionarios);

  free(funcionarios);

  return 0;
}

Reg adicionarFuncionario(Reg *funcionarios, Reg novoFuncionario)
{
  int size = numeroFuncionariosRegistrados(funcionarios);

  funcionarios = realloc(funcionarios, (size + 1) * sizeof(Reg));

  funcionarios[size] = novoFuncionario;

  return *funcionarios;
}

void menuPrincipal(Reg *funcionarios)
{
  int opcao;

  do
  {
    menu();
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
      adicionarFuncionario(funcionarios, criarFuncionario());
      break;

    case 2:
      int pagina = 0;

      int numeroFuncionarios = numeroFuncionariosRegistrados(funcionarios);

      int final = numeroFuncionariosRegistrados;

      if (numeroFuncionarios > (pagina + 1) * LIMITE_LISTAGEM)
      {
        final = (pagina + 1) * LIMITE_LISTAGEM;
      }

      listarFuncionarios(funcionarios, pagina, final);
      break;

    case 3:
      // buscarFuncionario(funcionarios);
      break;
    case 4:
      // alterarFuncionario(funcionarios);
      break;
    case 5:
      // deletarFuncionario(funcionarios);
      break;
    case 6:
      // totalSalariosPorCategoria(funcionarios);
      break;
    case 7:
      // maiorMenorSalarioPorCategoria(funcionarios);
      break;
    case 8:
      // mediaIdadePorCategoria(funcionarios);
      break;
    case 9:
      // quantidadeFuncionariosPorSalario(funcionarios);
      break;
    case 10:
      // nomeFuncionarioMaisNovo(funcionarios);
      break;
    case 11:
      printf("Saindo...\n");
      break;

    default:
      printf("Opcao invalida! Digite novamente.\n");
      break;
    }
  } while (opcao != 6);
}

void gerarFuncionariosAleatorios(Reg *funcionarios)
{
  for (int i = 0; i < GERAR_FUNCIONARIOS_ALEATORIOS; i++)
  {
    adicionarFuncionario(funcionarios, criarFuncionarioAleatorio(funcionarios));
  }
}

void menu()
{
  printf("Escolha uma opcao:\n");
  printf("1- Cadastrar funcionario\n");
  printf("2- Listar funcionarios\n");
  printf("3- Buscar funcionario por nome (nao implementado)\n");
  printf("4- Alterar dados de um funcionario (nao implementado)\n");
  printf("5- Deletar funcionario por id (nao implementado)\n");
  printf("6- Total de salarios por categoria (nao implementado)\n");
  printf("7- Maior e menor salario por categoria (nao implementado)\n");
  printf("8- Media de idade por categoria (nao implementado)\n");
  printf("9- Quantidade de funcionarios por salario (nao implementado)\n");
  printf("10- Nome do funcionario mais novo (nao implementado)\n");
  printf("11- Sair\n");
}

void informacoesFuncionario()
{
  printf("ID\t\tNOME\t\t\tSALARIO\t\tCATEGORIA\tIDADE\n");
}

void mostrarFuncionario(Reg funcionario)
{
  informacoesFuncionario();
  printf("%d\t\t%s\t\t\t%.2f\t\t%s\t\t%d\n",
         funcionario.id,
         funcionario.nome,
         funcionario.salario,
         nomeCategoria(funcionario.categoria),
         funcionario.idade);
}

Reg criarFuncionarioAleatorio(Reg *funcionarios)
{
  Reg novoFuncionario;

  int numeroDeFuncionarios = numeroDeFuncionariosRegistrados(funcionarios);

  int categoriaAleatoria = rand() % 3 + 1;
  double salarioAleatorio = rand() % 100000 + 1000;
  int idadeAleatoria = rand() % 60 + 18;

  novoFuncionario.id = gerarId();
  strcpy(novoFuncionario.nome, "Funcionario " + (numeroDeFuncionarios + 1));
  novoFuncionario.categoria = categoriaAleatoria;
  novoFuncionario.salario = salarioAleatorio;
  novoFuncionario.idade = idadeAleatoria;

  return novoFuncionario;
}

void listarFuncionarios(Reg *funcionarios, int pagina, int final)
{
  if (pagina == 0)
  {
    printf("Listando funcionarios...\n\n");
  }

  printf("Pagina %d\n\n", pagina + 1);

  informacoesFuncionario();

  for (int i = pagina * LIMITE_LISTAGEM; i < final; i++)
  {
    if (funcionarios[i].id == 0)
    {
      continue;
    }

    printf("%d\t%s\t\t%s\t\t%.2lf\t\t%d\n",
           funcionarios[i].id,
           funcionarios[i].nome,
           nomeCategoria(funcionarios[i].categoria),
           funcionarios[i].salario,
           funcionarios[i].idade);
  }

  int opcao;

  do
  {
    printf("Há mais funcionários, deseja ir para próxima página?\n");
    printf("1- Sim\n");
    printf("2- Nao\n");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1:
      listarFuncionarios(funcionarios, pagina + 1, final + LIMITE_LISTAGEM);
      break;
    case 2:
      break;
    default:
      printf("Opcao invalida! Digite novamente.\n");
    }
  } while (opcao != 1 && opcao != 2);
}

Reg criarFuncionario()
{
  Reg funcionario;

  funcionario.id = gerarId();
  strcpy(funcionario.nome, cadastraNome());
  funcionario.categoria = cadastraCategoria();
  funcionario.salario = cadastraSalario();
  funcionario.idade = cadastraIdade();

  printf("Funcionario criado com sucesso!\n");

  return funcionario;
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

char *cadastraNome()
{

  char *nome = malloc(20 * sizeof(char));

  printf("Digite o nome do funcionario: ");
  fgets(nome, 20, stdin);
  limparFgets(nome);

  return nome;
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

int numeroFuncionariosRegistrados(Reg *funcionarios)
{
  int i = 0;

  while (funcionarios[i].nome != '\0')
  {
    i++;
  }

  return i;
}

int gerarId()
{
  quantidadeFuncionarios++;

  return quantidadeFuncionarios;
}

void limparFgets(char *string)
{
  string[strcspn(string, "\r\n")] = '\0';
}

void limparBuffer()
{
  while (getchar() != '\n' && getchar() != '\r')
  {
  }
}
