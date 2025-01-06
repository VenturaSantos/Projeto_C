#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAMANHO_STRING_LONGA 80
#define TAMANHO_STRING_MEDIA 65
#define TAMANHO_STRING_CURTA 20
#define MAXIMO_ESTUDANTES 100
#define MAXIMO_FICHAS 10
#define MAXIMO_EXERCICIOS_POR_FICHAS 10
#define MAXIMO_EXERCICIOS 100

typedef struct
{
    int id_unico_estudante;
    int numero_do_estudante;
    char nome_do_estudante[TAMANHO_STRING_LONGA];
    char email_do_estudante[TAMANHO_STRING_MEDIA];
} t_estudante;

typedef struct
{
    int dia;
    int mes;
    int ano;
} t_data;

typedef struct
{
    int id_unico_ficha;
    char nome_da_ficha[TAMANHO_STRING_LONGA];
    int numero_de_exercicios;
    int exercicios_guardados;
    t_data data_de_publicacao;
} t_ficha_de_exercicios;

typedef struct
{
    int id_unico_exercicio;
    char nome_do_exercicio[TAMANHO_STRING_LONGA];
    char dificuldade[TAMANHO_STRING_CURTA];
    char tipo_solucao[TAMANHO_STRING_CURTA];
    t_ficha_de_exercicios id_ficha;
} t_exercicio;

// Funções dados estudantes
int inserir_dados_estudantes(t_estudante alunos[], int quantidade_alunos);
int verifica_numero_estudante(t_estudante alunos[], int quantidade_alunos);
int verifica_existencia_numero_estudante(char pedido_informacao[], t_estudante alunos[], int total_de_estudantes);
int procurar_estudante(t_estudante alunos[], int numeroEstudantes, int numeroEstudante);
void ver_dados_estudantes(t_estudante alunos[], int id_do_estudante);

// Funções dados fichas
int inserir_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_de_fichas);
void insira_verifica_nome_ficha(char pedido_de_informacao[], t_ficha_de_exercicios fichas[], int quantidade_de_fichas);
void insira_verifica_exercicios_da_ficha(char pedido_informacao[], t_ficha_de_exercicios fichas[], int quantidade_fichas);
void insira_verifica_data(int *dia, int *mes, int *ano, char info_mensagem[]);
void ver_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_de_fichas);

// Funções dados exercícios
int inserir_dados_exercicios(t_exercicio exercicios[], int quantidade_exercicios, t_ficha_de_exercicios fichas[], int quantidade_fichas);
int insira_verifica_id_ficha(t_ficha_de_exercicios fichas[], int quantidade_fichas);
void ler_dificuldade_exercicio(char classificacao[]);
void ler_tipo_solucao_exercicio(char solucao[]);
void verifica_existencia_id_exercicios(t_exercicio exercicios[], int quantidade_exercicios);
void ver_dados_exercicios(t_exercicio exercicios[], int id_exercicios);

// Faltam as Funções relacionadass com os ficheiros

int main()
{
}

// Funções dados estudantes

// Função para ler os dados dos estudantess
int inserir_dados_estudantes(t_estudante alunos[], int quantidade_alunos)
{
    t_estudante Estudante;
    Estudante.id_unico_estudante = quantidade_alunos + 1;

    printf("Numero do Estudante: ");
    scanf("%d", &Estudante.numero_do_estudante);

    printf("Nome do Estudante: ");
    scanf(" %[^\n]s", Estudante.nome_do_estudante);

    printf("Email do Estudante: ");
    scanf("%d", &Estudante.email_do_estudante);

    alunos[quantidade_alunos] = Estudante;

    return quantidade_alunos + 1;
}

// Função para ver os dados dos Estudantes
void ver_dados_estudantes(t_estudante alunos[], int id_do_estudante)
{
    // podemos fazer-validação do id
    printf("\nEstudante %d:\n", alunos[id_do_estudante].id_unico_estudante);
    printf("Numero: %d\n", alunos[id_do_estudante].numero_do_estudante);
    printf("Nome: %s\n", alunos[id_do_estudante].nome_do_estudante);
    printf("Email: %s\n", alunos[id_do_estudante].email_do_estudante);
}


// Funções dados fichas

// Função para Inserir os dados das Fichas
int inserir_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_de_fichas)
{
    t_ficha_de_exercicios FichaExercicios;
    FichaExercicios.id_unico_ficha = quantidade_de_fichas + 1;

    printf("Nome da Ficha: ");
    scanf("%d", &FichaExercicios.nome_da_ficha);

    printf("Numero de Exercicios: ");
    scanf(" %[^\n]s", FichaExercicios.numero_de_exercicios);

    printf("Data de Publicação: ");
    scanf("%d", &FichaExercicios.data_de_publicacao);

    fichas[quantidade_de_fichas] = FichaExercicios;

    return quantidade_de_fichas + 1;
}

// Função para ver os dados das fichas
void ver_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_de_fichas)
{

    // podemos fazer-validação do id
    printf("\nEstudante %d:\n", fichas[quantidade_de_fichas].id_unico_ficha);
    printf("Numero: %d\n", fichas[quantidade_de_fichas].nome_da_ficha);
    printf("Nome: %s\n", fichas[quantidade_de_fichas].numero_de_exercicios);
    printf("Email: %s\n", fichas[quantidade_de_fichas].data_de_publicacao);
}




// Funções dados exercícios

// Função para inserir os dados dos exercicios
int inserir_dados_exercicios(t_exercicio exercicios[], int quantidade_exercicios, t_ficha_de_exercicios fichas[], int quantidade_fichas)
{
    if (quantidade_exercicios >= MAXIMO_EXERCICIOS)
    {
        printf("A quantidade máxima de exercicios foi atingida\n");
    }
    else
    {
        exercicios[quantidade_exercicios].id_unico_exercicio = quantidade_exercicios + 1;
        exercicios[quantidade_exercicios].id_ficha.id_unico_ficha; //preciso e criar a função = insira_verifica_id_ficha_exericios(fichas, quantidade_Fichas);

        printf("Escreva o nome do Exercicio");
        getchar();
        fgets(exercicios[quantidade_exercicios].nome_do_exercicio, TAMANHO_STRING_LONGA, stdin);
        exercicios[quantidade_exercicios].nome_do_exercicio[strcspn(exercicios[quantidade_exercicios].nome_do_exercicio, "\n")] = 0;

        ler_dificuldade_exercicio(exercicios[quantidade_exercicios].dificuldade);

        ler_tipo_solucao_exercicio(exercicios[quantidade_exercicios].tipo_solucao);
        quantidade_exercicios = quantidade_exercicios + 1;
    }
    return quantidade_exercicios;
}

// Função para ler a Dificuldade da ficha
void ler_dificuldade_exercicio(char classificacao[])
{

    int dificuldade;
    do
    {
        printf("\n Qual é a dificuldade do Exercicio:");
        printf("(1) Baixo");
        printf("(2) Medio");
        printf("(3) Elevado");
        printf("Opção -->: ");
        scanf("%d", &dificuldade);
    } while (dificuldade != 1 && dificuldade != 2 && dificuldade != 3);

    if (dificuldade == 1)
    {
        strcpy(classificacao, "Baixo");
    }

    if (dificuldade == 2)
    {
        strcpy(classificacao, "Medio");
    }

    if (dificuldade == 3)
    {
        strcpy(classificacao, "Elevado");
    }
}

// Função para ler o tipo de solução
void ler_tipo_solucao_exercicio(char solucao[])
{

    int dificuldade;
    do
    {
        printf("\n Qual é o tipo de Solução?");
        printf("(1) Algoritmo");
        printf("(2) Código");
        printf("Opção -->: ");
        scanf("%d", &dificuldade);
    } while (dificuldade != 1 && dificuldade != 2);

    if (dificuldade == 1)
    {
        strcpy(solucao, "Algoritmo");
    }

    if (dificuldade == 2)
    {
        strcpy(solucao, "Código");
    }
}