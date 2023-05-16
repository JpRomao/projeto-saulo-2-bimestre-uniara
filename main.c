/**
 * Projeto no GitHub: https://github.com/JpRomao/projeto-saulo-2-bimestre-uniara
 * Documentação do projeto: https://fourth-metatarsal-651.notion.site/Documenta-o-projeto-Saulo-2-Bimestre-e3cbab03739943ab84ff2f65410a589a
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** VARIÁVIES DE TESTE */
// Mudar para 'PROD' para rodar em producao e 'TEST' para rodar em testes
#define AMBIENTE "TEST"
// Mudar esta variável irá resultar na mudança da quantidade de funcionários gerados aleatoriamente
#define GERAR_FUNCIONARIOS_ALEATORIOS 3
/***/

#define IDADE_MINIMA 18
#define IDADE_MAXIMA 65
#define SALARIO_MINIMO 1000.0
#define SALARIO_MAXIMO 100000.0
// Mudar esse numero irá resultar na mudança da quantidade de funcionarios listados por pagina
#define LIMITE_LISTAGEM 10

typedef struct Funcionario
{
  int id;
  char nome[20];
  double salario;
  int categoria;
  int idade;
} Reg;

int quantidadeFuncionarios = 0;

/** Funções disponíveis */
void limparBuffer();
void limparFgets(char *string);
void menuPrincipal(Reg *funcionarios, int jaFoiOrdenado);
void informacoesFuncionario();
void listarFuncionarios(Reg *funcionarios, int pagina, int numeroFuncionarios);
void mostrarFuncionario(Reg funcionario);
void menu();
void ordenarPorNome(Reg *funcionarios);
void totalSalariosPorCategoria(Reg *funcionarios);
void mediaIdadePorCategoria(Reg *funcionarios);
void quantidadeFuncionariosComSalarioMinimo(Reg *funcionarios);
void funcionariosComMaiorEMenorSalarioPorCategoria(Reg *funcionarios);
int gerarId();
int cadastraIdade();
int cadastraCategoria();
int perguntarSimOuNao();
int tamanhoArrayFuncionarios(Reg *funcionarios);
char *cadastraNome();
char *nomeCategoria(int categoria);
char *transformarStringParaMinusculo(char *string);
double cadastraSalario();
Reg criarFuncionario(int estaAlterando, int id);
Reg criarFuncionarioAleatorio();
Reg funcionarioComMaiorSalario(Reg *funcionarios);
Reg funcionarioComMenorSalario(Reg *funcionarios);
Reg *buscarFuncionarioPorNomeContendo(Reg *funcionarios, Reg *funcionariosEncontrados, int *quantidadeFuncionariosEncontrados);
Reg *adicionarFuncionario(Reg *funcionarios, Reg novoFuncionario);
Reg *gerarFuncionariosAleatorios(Reg *funcionarios);
Reg *deletarFuncionario(Reg *funcionarios);
Reg *nomeFuncionarioMaisNovo(Reg *funcionario);
Reg *alterarFuncionario(Reg *funcionarios);
/***/

void menuPrincipal(Reg *funcionarios, int jaFoiOrdenado)
{
  int opcao;

  if (strcmp(AMBIENTE, "TEST") == 0)
  {
    funcionarios = gerarFuncionariosAleatorios(funcionarios);
  }

  if (!jaFoiOrdenado)
  {
    ordenarPorNome(funcionarios);

    jaFoiOrdenado = 1;
  }

  int quantidadeFuncionariosPesquisados = 0;
  Reg *funcionariosPesquisados;

  do
  {
    menu();
    scanf("%d", &opcao);
    limparBuffer();

    int pagina = 1;

    switch (opcao)
    {
    case 1:
      funcionarios = adicionarFuncionario(funcionarios, criarFuncionario(0, 0));

      jaFoiOrdenado = 0;
      break;
    case 2:
      listarFuncionarios(funcionarios, pagina, quantidadeFuncionarios);
      break;

    case 3:
      funcionariosPesquisados = buscarFuncionarioPorNomeContendo(funcionarios, funcionariosPesquisados, &quantidadeFuncionariosPesquisados);

      printf("Foram encontrados %d funcionarios com o nome pesquisado.\n", quantidadeFuncionariosPesquisados);

      listarFuncionarios(funcionariosPesquisados, pagina, quantidadeFuncionariosPesquisados);
      break;
    case 4:
      alterarFuncionario(funcionarios);
      jaFoiOrdenado = 0;
      break;
    case 5:
      deletarFuncionario(funcionarios);
      break;
    case 6:
      totalSalariosPorCategoria(funcionarios);
      break;
    case 7:
      funcionariosComMaiorEMenorSalarioPorCategoria(funcionarios);
      break;
    case 8:
      mediaIdadePorCategoria(funcionarios);
      break;
    case 9:
      quantidadeFuncionariosComSalarioMinimo(funcionarios);
      break;
    case 10:
      nomeFuncionarioMaisNovo(funcionarios);
      break;
    case 11:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 11);
}

int main()
{
  Reg *funcionarios = malloc(quantidadeFuncionarios * sizeof(Reg));

  int jaFoiOrdenado = 0;

  menuPrincipal(funcionarios, jaFoiOrdenado);

  free(funcionarios);

  return 0;
}

/** Implementação das funções */

void ordenarPorNome(Reg *funcionarios)
{
  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    for (int j = 0; j < quantidadeFuncionarios; j++)
    {
      if (strcmp(funcionarios[i].nome, funcionarios[j].nome) < 0)
      {
        Reg aux = funcionarios[i];
        funcionarios[i] = funcionarios[j];
        funcionarios[j] = aux;
      }
    }
  }
}

void quantidadeFuncionariosComSalarioMinimo(Reg *funcionarios)
{
  const int ate2000 = 2000;
  const int ate4000 = 4000;
  const int ate6000 = 6000;
  const int ate8000 = 8000;
  const int mais8000 = 8001;

  int quantidadeAte2000 = 0;
  int quantidadeAte4000 = 0;
  int quantidadeAte6000 = 0;
  int quantidadeAte8000 = 0;
  int quantidadeMais8000 = 0;

  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    if (funcionarios[i].salario <= ate2000)
    {
      quantidadeAte2000++;
    }
    else if (funcionarios[i].salario <= ate4000)
    {
      quantidadeAte4000++;
    }
    else if (funcionarios[i].salario <= ate6000)
    {
      quantidadeAte6000++;
    }
    else if (funcionarios[i].salario <= ate8000)
    {
      quantidadeAte8000++;
    }
    else
    {
      quantidadeMais8000++;
    }
  }

  printf("Quantidade de funcionarios com salario ate 2000: %d\n", quantidadeAte2000);
  printf("Quantidade de funcionarios com salario ate 4000: %d\n", quantidadeAte4000);
  printf("Quantidade de funcionarios com salario ate 6000: %d\n", quantidadeAte6000);
  printf("Quantidade de funcionarios com salario ate 8000: %d\n", quantidadeAte8000);
  printf("Quantidade de funcionarios com salario acima de 8000: %d\n", quantidadeMais8000);
}

Reg *deletarFuncionario(Reg *funcionarios)
{
  int idFuncionario = 0;

  printf("Digite o id do funcionario que deseja deletar: ");
  scanf("%d", &idFuncionario);
  limparBuffer();

  if (idFuncionario == 0)
  {
    printf("Id invalido! Deseja tentar novamente?\n");

    int opcao = perguntarSimOuNao();

    if (opcao)
    {
      return deletarFuncionario(funcionarios);
    }
  }

  int i = 0;

  printf("Encontrando funcionario...");

  while (funcionarios[i].id != idFuncionario)
  {
    i++;

    if (i == quantidadeFuncionarios)
    {
      printf("Funcionario nao encontrado! Deseja tentar novamente?\n");

      int opcao = perguntarSimOuNao();

      if (opcao)
      {
        return deletarFuncionario(funcionarios);
      }
    }
  }

  printf("Deseja realmente deletar o funcionario %s?\n", funcionarios[i].nome);

  int opcao = perguntarSimOuNao();

  if (opcao)
  {
    for (int j = i; j < quantidadeFuncionarios; j++)
    {
      funcionarios[j] = funcionarios[j + 1];
    }

    funcionarios = realloc(funcionarios, (quantidadeFuncionarios - 1) * sizeof(Reg));

    printf("Funcionario deletado com sucesso!\n");

    quantidadeFuncionarios--;
  }
  else
  {
    printf("Funcionario nao deletado!\n");
  }

  return funcionarios;
}

Reg *alterarFuncionario(Reg *funcionarios)
{
  int idFuncionario = 0;

  printf("Digite o id do funcionario que deseja alterar: ");
  scanf("%d", &idFuncionario);
  limparBuffer();

  if (idFuncionario == 0)
  {
    printf("Id invalido! Deseja tentar novamente?\n");

    int opcao = perguntarSimOuNao();

    if (opcao)
    {
      return alterarFuncionario(funcionarios);
    }
  }

  int i = 0;

  printf("Encontrando funcionario...");

  while (funcionarios[i].id != idFuncionario)
  {
    i++;

    if (i == quantidadeFuncionarios)
    {
      printf("Funcionario nao encontrado! Deseja tentar novamente?\n");

      int opcao = perguntarSimOuNao();

      if (opcao)
      {
        return alterarFuncionario(funcionarios);
      }
    }
  }

  printf("Deseja realmente alterar o funcionario %s?\n", funcionarios[i].nome);

  int opcao = perguntarSimOuNao();

  if (opcao)
  {
    int estaAlterando = 1;

    Reg novoFuncionario = criarFuncionario(estaAlterando, funcionarios[i].id);

    funcionarios[i] = novoFuncionario;

    printf("Funcionario alterado com sucesso!\n");

    return funcionarios;
  }
  else
  {
    printf("Funcionario nao alterado!\n");
  }
}

void totalSalariosPorCategoria(Reg *funcionarios)
{
  double totalGerencia = 0;
  double totalSupervisao = 0;
  double totalOperacional = 0;

  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    switch (funcionarios[i].categoria)
    {
    case 1:
      totalGerencia += funcionarios[i].salario;
      break;

    case 2:
      totalSupervisao += funcionarios[i].salario;
      break;

    case 3:
      totalOperacional += funcionarios[i].salario;
      break;
    }
  }

  printf("Total de salarios categoria Gerencia: %.2lf\n", totalGerencia);
  printf("Total de salarios categoria Supervisao: %.2lf\n", totalSupervisao);
  printf("Total de salarios categoria Operacional: %.2lf\n", totalOperacional);
}

void mediaIdadePorCategoria(Reg *funcionarios)
{
  int totalGerencia = 0;
  int totalSupervisao = 0;
  int totalOperacional = 0;
  int contGerencia = 0;
  int contSupervisao = 0;
  int contOperacional = 0;

  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    switch (funcionarios[i].categoria)
    {
    case 1:
      totalGerencia += funcionarios[i].idade;
      contGerencia++;
      break;

    case 2:
      totalSupervisao += funcionarios[i].idade;
      contSupervisao++;
      break;

    case 3:
      totalOperacional += funcionarios[i].idade;
      contOperacional++;
      break;
    }
  }
  int mediaGerencia = totalGerencia / contGerencia;
  int mediaSupervisao = totalSupervisao / contSupervisao;
  int mediaOperacional = totalOperacional / contOperacional;

  printf("Media de idade da categoria Gerencia: %d\n", mediaGerencia);
  printf("Media de idade da categoria Supervisao: %d\n", mediaSupervisao);
  printf("Media de idade da categoria Operacional: %d\n", mediaOperacional);
}

Reg *nomeFuncionarioMaisNovo(Reg *funcionarios)
{
  Reg *funcionarioMaisNovo = &funcionarios[0];

  for (int i = 1; i < quantidadeFuncionarios; i++)
  {
    if (funcionarios[i].idade < funcionarioMaisNovo->idade)
    {
      funcionarioMaisNovo = &funcionarios[i];
    }
  }

  printf("Funcionario mais novo: \n");
  informacoesFuncionario();
  mostrarFuncionario(*funcionarioMaisNovo);

  return funcionarioMaisNovo;
}

int perguntarSimOuNao()
{
  int opcao;

  printf("1 - Sim\n");
  printf("2 - Nao\n");
  scanf("%d", &opcao);
  limparBuffer();

  if (opcao == 1)
  {
    return 1;
  }
  else if (opcao == 2)
  {
    return 0;
  }
  else
  {
    printf("Opcao invalida!\n");

    return perguntarSimOuNao();
  }
}

Reg *buscarFuncionarioPorNomeContendo(Reg *funcionarios, Reg *funcionariosEncontrados, int *quantidadeFuncionariosEncontrados)
{
  char nomeFuncionario[20] = "";

  printf("Digite o nome do funcionario que deseja buscar\n");
  strcpy(nomeFuncionario, cadastraNome());

  char *nomeEmMinusculo = transformarStringParaMinusculo(nomeFuncionario);

  funcionariosEncontrados = malloc((*quantidadeFuncionariosEncontrados) * sizeof(Reg));

  for (int i = 0, j = 0; i < quantidadeFuncionarios; i++)
  {
    char *nomeFuncionarioEmMinusculo = transformarStringParaMinusculo(funcionarios[i].nome);

    if (strstr(nomeFuncionarioEmMinusculo, nomeEmMinusculo))
    {
      funcionariosEncontrados = realloc(funcionariosEncontrados, (j + 1) * sizeof(Reg));
      funcionariosEncontrados[j] = funcionarios[i];
      j++;
      *quantidadeFuncionariosEncontrados = j;
    }
  }

  return funcionariosEncontrados;
}

char *transformarStringParaMinusculo(char *string)
{
  char *stringMinusculo = (char *)malloc(strlen(string) + 1);
  strcpy(stringMinusculo, string);

  for (int i = 0; string[i]; i++)
  {
    stringMinusculo[i] = tolower(string[i]);
  }

  return stringMinusculo;
}

Reg *adicionarFuncionario(Reg *funcionarios, Reg novoFuncionario)
{
  int indice = quantidadeFuncionarios - 1;

  funcionarios = realloc(funcionarios, (quantidadeFuncionarios + 1) * sizeof(Reg));
  funcionarios[indice].categoria = novoFuncionario.categoria;
  funcionarios[indice].idade = novoFuncionario.idade;
  funcionarios[indice].salario = novoFuncionario.salario;
  funcionarios[indice].id = novoFuncionario.id;
  strcpy(funcionarios[indice].nome, novoFuncionario.nome);

  return funcionarios;
}

Reg *gerarFuncionariosAleatorios(Reg *funcionarios)
{
  for (int i = 0; i < GERAR_FUNCIONARIOS_ALEATORIOS; i++)
  {
    Reg novoFuncionario = criarFuncionarioAleatorio();

    funcionarios = adicionarFuncionario(funcionarios, novoFuncionario);
  }

  return funcionarios;
}

void menu()
{
  printf("Escolha uma opcao:\n");
  printf("1- Cadastrar funcionario\n");
  printf("2- Listar funcionarios\n");
  printf("3- Buscar funcionario por nome\n");
  printf("4- Alterar dados de um funcionario\n");
  printf("5- Deletar funcionario por id\n");
  printf("6- Total de salarios por categoria\n");
  printf("7- Maior e menor salario por categoria\n");
  printf("8- Media de idade por categoria\n");
  printf("9- Quantidade de funcionarios por salario\n");
  printf("10- Nome do funcionario mais novo\n");
  printf("11- Sair\n");
}

void imprimirLinha()
{
  printf("---------------------------------------------------------------------------------------------------------------------------\n");
}

void informacoesFuncionario()
{
  imprimirLinha();
  printf("ID\t\tNOME\t\t\tSALARIO\t\tCATEGORIA\t\tIDADE\n");
}

int tamanhoArrayFuncionarios(Reg *funcionarios)
{
  int tamanho = 0;

  while (funcionarios[tamanho].id != 0)
  {
    tamanho++;
  }

  return tamanho;
}

void mostrarFuncionario(Reg funcionario)
{
  printf("%d\t\t%s\t\t%.2f\t\t%s\t\t%d\n",
         funcionario.id,
         funcionario.nome,
         funcionario.salario,
         nomeCategoria(funcionario.categoria),
         funcionario.idade);
  printf("\n");
}

Reg criarFuncionarioAleatorio()
{
  printf("Criando funcionario aleatorio...\n");

  Reg novoFuncionario;

  int categoriaAleatoria = rand() % 3 + 1;
  double salarioAleatorio = rand() % 100000 + 1000;
  int idadeAleatoria = rand() % IDADE_MAXIMA + 18;

  novoFuncionario.id = gerarId();

  strcpy(novoFuncionario.nome, "Funcionario ");
  char *numeroDeFuncionariosString = (char *)malloc(sizeof(char) * novoFuncionario.id);
  sprintf(numeroDeFuncionariosString, "%d", novoFuncionario.id);
  strcat(novoFuncionario.nome, numeroDeFuncionariosString);

  novoFuncionario.categoria = categoriaAleatoria;
  novoFuncionario.salario = salarioAleatorio;
  novoFuncionario.idade = idadeAleatoria;

  return novoFuncionario;
}

void listarFuncionarios(Reg *funcionarios, int pagina, int numeroFuncionarios)
{
  int final = numeroFuncionarios;

  if (numeroFuncionarios > pagina * LIMITE_LISTAGEM)
  {
    final = pagina * LIMITE_LISTAGEM;
  }

  if (pagina == 1)
  {
    printf("Listando funcionarios...\n\n");
  }

  printf("\nPagina %d:\n", pagina);

  int inicio = (pagina - 1) * LIMITE_LISTAGEM;

  informacoesFuncionario();
  for (int i = inicio; i < final; i++)
  {
    mostrarFuncionario(funcionarios[i]);
  }
  imprimirLinha();

  if (numeroFuncionarios > final)
  {
    int usuarioDesejaVerProximaPagina = perguntarSimOuNao();

    if (usuarioDesejaVerProximaPagina)
    {
      listarFuncionarios(funcionarios, pagina + 1, numeroFuncionarios);
    }
  }
}

Reg criarFuncionario(int estaAlterando, int id)
{
  Reg funcionario;

  if (estaAlterando)
  {
    funcionario.id = gerarId();
  }
  else
  {
    funcionario.id = id;
  }

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

  if (salario < SALARIO_MINIMO)
  {
    printf("Salário abaixo do permitido. Digite um salário igual ou acima de: %.2lf", SALARIO_MINIMO);
  }
  else if (salario > SALARIO_MAXIMO)
  {
    printf("Salário acima do permitido. Digite um salário igual ou abaixo de: %.2lf", SALARIO_MAXIMO);
  }

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

  printf("Digite a idade do funcionario: ");
  scanf("%d", &idade);
  limparBuffer();

  if (idade < IDADE_MINIMA)
  {
    printf("A idade digitada eh invalida! A idade precisa ser igual ou superior a: %d", IDADE_MINIMA);

    return cadastraIdade();
  }
  else if (idade > IDADE_MAXIMA)
  {
    printf("A idade digitada eh invalida! A idade precisa ser igual ou inferior a: %d", IDADE_MAXIMA);

    return cadastraIdade();
  }

  return idade;
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

Reg funcionarioComMenorSalario(Reg *funcionarios)
{
  Reg funcionarioComMenorSalario = funcionarios[0];

  for (int i = 1; i < tamanhoArrayFuncionarios(funcionarios); i++)
  {
    if (funcionarios[i].salario < funcionarioComMenorSalario.salario)
    {
      funcionarioComMenorSalario = funcionarios[i];
    }
  }

  return funcionarioComMenorSalario;
}

Reg funcionarioComMaiorSalario(Reg *funcionarios)
{
  Reg funcionarioComMaiorSalario = funcionarios[0];

  for (int i = 1; i < tamanhoArrayFuncionarios(funcionarios); i++)
  {
    if (funcionarios[i].salario > funcionarioComMaiorSalario.salario)
    {
      funcionarioComMaiorSalario = funcionarios[i];
    }
  }

  return funcionarioComMaiorSalario;
}

void funcionariosComMaiorEMenorSalarioPorCategoria(Reg *funcionarios)
{
  int quantidadeFuncionariosGerencia = 0;
  int quantidadeFuncionariosSupervisao = 0;
  int quantidadeFuncionariosOperacional = 0;

  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    if (funcionarios[i].categoria == 1)
    {
      quantidadeFuncionariosGerencia++;
    }
    else if (funcionarios[i].categoria == 2)
    {
      quantidadeFuncionariosSupervisao++;
    }
    else if (funcionarios[i].categoria == 3)
    {
      quantidadeFuncionariosOperacional++;
    }
  }

  Reg *funcionariosGerencia = malloc(quantidadeFuncionariosGerencia * sizeof(Reg));
  Reg *funcionariosSupervisao = malloc(quantidadeFuncionariosSupervisao * sizeof(Reg));
  Reg *funcionariosOperacional = malloc(quantidadeFuncionariosOperacional * sizeof(Reg));

  int indiceFuncionariosGerencia = 0;
  int indiceFuncionariosSupervisao = 0;
  int indiceFuncionariosOperacional = 0;

  for (int i = 0; i < quantidadeFuncionarios; i++)
  {
    if (funcionarios[i].categoria == 1)
    {
      funcionariosGerencia[indiceFuncionariosGerencia] = funcionarios[i];
      indiceFuncionariosGerencia++;
    }
    else if (funcionarios[i].categoria == 2)
    {
      funcionariosSupervisao[indiceFuncionariosSupervisao] = funcionarios[i];
      indiceFuncionariosSupervisao++;
    }
    else if (funcionarios[i].categoria == 3)
    {
      funcionariosOperacional[indiceFuncionariosOperacional] = funcionarios[i];
      indiceFuncionariosOperacional++;
    }
  }

  Reg funcionarioComMaiorSalarioGerencia = funcionarioComMaiorSalario(funcionariosGerencia);
  Reg funcionarioComMenorSalarioGerencia = funcionarioComMenorSalario(funcionariosGerencia);

  Reg funcionarioComMaiorSalarioSupervisao = funcionarioComMaiorSalario(funcionariosSupervisao);
  Reg funcionarioComMenorSalarioSupervisao = funcionarioComMenorSalario(funcionariosSupervisao);

  Reg funcionarioComMaiorSalarioOperacional = funcionarioComMaiorSalario(funcionariosOperacional);
  Reg funcionarioComMenorSalarioOperacional = funcionarioComMenorSalario(funcionariosOperacional);

  printf("\nFuncionario com maior salario na categoria Gerencia: %d - %s\n", funcionarioComMaiorSalarioGerencia.id, funcionarioComMaiorSalarioGerencia.nome);
  printf("Funcionario com menor salario na categoria Gerencia: %d - %s\n", funcionarioComMenorSalarioGerencia.id, funcionarioComMenorSalarioGerencia.nome);

  printf("\nFuncionario com maior salario na categoria Supervisao: %d - %s\n", funcionarioComMaiorSalarioSupervisao.id, funcionarioComMaiorSalarioSupervisao.nome);
  printf("Funcionario com menor salario na categoria Supervisao: %d - %s\n", funcionarioComMenorSalarioSupervisao.id, funcionarioComMenorSalarioSupervisao.nome);

  printf("\nFuncionario com maior salario na categoria Operacional: %d - %s\n", funcionarioComMaiorSalarioOperacional.id, funcionarioComMaiorSalarioOperacional.nome);
  printf("Funcionario com menor salario na categoria Operacional: %d - %s\n", funcionarioComMenorSalarioOperacional.id, funcionarioComMenorSalarioOperacional.nome);
}
