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
void insira_verifica_data(int *dia, int  *mes, int *ano, char info_mensagem[]);
void ver_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_de_fichas);

// Funções dados exercícios
int inserir_dados_exercicios(t_exercicio exercicios[], int quantidade_exercicios, t_ficha_de_exercicios fichas[], int quantidade_fichas);
int insira_verifica_id_ficha(t_ficha_de_exercicios fichas[], int quantidade_fichas);
void ler_dificuldade_exercicio(char classificacao[]);
void ler_tipo_solucao_exercicio(char solucao[]);
void verifica_existencia_id_exercicios(t_exercicio exercicios[], int quantidade_exercicios);
void ver_dados_exercicios(t_exercicio exercicios[], int id_exercicios);


/* ADICIONANDO LINHAS NO CODE PARA TESTAR O GIT AH EH IH OH AUUUUUU ANIMALS ANIMALS*/