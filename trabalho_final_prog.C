#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAMANHO_STRING_LONGA 80
#define MAXIMO_EXERCICIOS 100
#define TAMANHO_STRING_CURTA 20
#define MAXIMO_ESTUDANTES 100
#define MAXIMO_EXERCICIOS_POR_FICHAS 10
#define MAXIMO_FICHAS 10

typedef struct
{
    int id_unico_estudante;
    int numero_do_estudante;
    char nome_do_estudante[TAMANHO_STRING_LONGA];
    char email_do_estudante[TAMANHO_STRING_LONGA];  //TAMANHO STRING, SO NAO BASTA TER O LONGA??
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
int verifica_existencia_id_estudante(char pedido_informacao[], t_estudante alunos[], int total_de_estudantes);
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
void verifica_existencia_id_exercicios(t_exercicio exercicios[], int quantidade_exercicios);  //falta verificar a existencia de id
void ver_dados_exercicios(t_exercicio exercicios[], int id_exercicios);


// Faltam as Funções relacionadass com os ficheiros
//GUARDAR INFORMAÇOES EM FICHEIROS
void guardar_estudantes(t_estudante alunos[], int quantidade_alunos, const char* filename);
void guardar_fichas(t_ficha_de_exercicios fichas[], int quantidade_fichas, const char* filename);
void guardar_exercicios(t_exercicio exercicios[], int quantidade_exercicios, const char* filename);
void guardar_todos_dados(t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas, t_exercicio exercicios[], int quantidade_exercicios);

//DAR LOAD à DATA dos ficheiros
int load_estudantes(t_estudante alunos[], const char* filename);
int load_fichas(t_ficha_de_exercicios fichas[], const char* filename);
int load_exercicios(t_exercicio exercicios[], const char* filename);
void load_todos_dados(t_estudante alunos[], t_ficha_de_exercicios fichas[], t_exercicio exercicios[]);



//FUNCAO MAIN

main() {
    t_estudante alunos[MAXIMO_ESTUDANTES];
    t_ficha_de_exercicios fichas[MAXIMO_FICHAS];
    t_exercicio exercicios[MAXIMO_EXERCICIOS];
    int quantidade_alunos = 0, quantidade_fichas = 0, quantidade_exercicios = 0;

    // Load data from files if available
    load_todos_dados(alunos, fichas, exercicios);

    // Insert new students, exercises, etc. (use the existing functions)

    // Save the data back to files
    guardar_todos_dados(alunos, quantidade_alunos, fichas, quantidade_fichas, exercicios, quantidade_exercicios);

    return 0;
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
    scanf(" %[^\n]s", &Estudante.email_do_estudante);  // [^\n] , o ^ condição de negação , ou seja, enquanto nao houver mudança de linha pode se continuar a escrever até o tamanho max da string

    alunos[quantidade_alunos] = Estudante;

    return quantidade_alunos + 1; // incrementação dos estudantes
}

//verificação do numero do estudante
int verifica_numero_estudante(t_estudante alunos[], int quantidade_alunos) 
{
    int indice;
    int numeroEstudante;
    printf("Insira o numero do estudante a verificar: ");
    scanf("%d", &numeroEstudante);

    for (int indice; indice < quantidade_alunos; indice++) 
    {
        if (alunos[indice].numero_do_estudante == numeroEstudante) 
        {
            printf("O numero de estudante já existe.\n");
            return 1; 
        }
    }

    printf("O numero do estudante não existe.\n");
    return 0; 
}


//verificar se o id existe
int verifica_existencia_id_estudante(int id, t_estudante alunos[], int total_de_estudantes)
{
    int index = 0;
    for (index; index < total_de_estudantes; index++)
    {
        if(alunos[index].id_unico_estudante ==id)
        {
            return 1;
        }
    }
    return 0;
}

// Procura o nome do estudante
int procurar_estudante(t_estudante alunos[], int numeroEstudantes, int numeroEstudante) 
{
    int index=0;

    for (index; index < numeroEstudantes; index++) 
    {
        if (alunos[index].numero_do_estudante == numeroEstudante) 
        {
            return index; 
        }
    }
    return -1; 
}


// Função para ver os dados dos Estudantes
void ver_dados_estudantes(t_estudante alunos[], int id_do_estudante)
{
    // podemos fazer-validação do id     id_do_estudante - 1  para dar o index certo 1º estudante -> index 0
    printf("\nEstudante %d:\n", alunos[id_do_estudante - 1].id_unico_estudante);
    printf("Numero: %d\n", alunos[id_do_estudante - 1].numero_do_estudante);
    printf("Nome: %s\n", alunos[id_do_estudante - 1].nome_do_estudante);
    printf("Email: %s\n", alunos[id_do_estudante -1 ].email_do_estudante);
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

//Função com objetivo verificar se ja existe uma ficha com o mesmo nome
void insira_verifica_nome_ficha(char pedido_de_informacao[], t_ficha_de_exercicios fichas[], int quantidade_de_fichas){

    int indice, existencia;

    do {
        existencia =0;

        printf("%s", pedido_de_informacao);
        getchar();
        fgets(fichas[quantidade_de_fichas].nome_da_ficha, TAMANHO_STRING_LONGA, stdin);
        fichas[quantidade_de_fichas].nome_da_ficha[strcspn(fichas[quantidade_de_fichas].nome_da_ficha, "\n")] =0;
        for (indice=0; indice < quantidade_de_fichas; indice++){

            if(strcmp(fichas[indice].nome_da_ficha, fichas[quantidade_de_fichas].nome_da_ficha) == 0){

                existencia =1;
                printf("O nome desta ficha já existe!!\n");
            }
        }
    } while (existencia);
}


//Função com objetivo de verificar se o numero de exercicios excedeu o limite por ficha
void insira_verifica_exercicios_da_ficha(char pedido_informacao[], t_ficha_de_exercicios fichas[], int quantidade_fichas){

    int quantidade_exercicios = 0;

    do {
        printf("%s", pedido_informacao);
        scanf("%d", &quantidade_exercicios);
        if (quantidade_exercicios <1 || quantidade_exercicios > MAXIMO_EXERCICIOS_POR_FICHAS)
        {
            printf("O numero de exercicios excedeu o limite por ficha (1- %d)!!\n", MAXIMO_EXERCICIOS_POR_FICHAS);
        }      
    } while (quantidade_exercicios < 1 || quantidade_exercicios > MAXIMO_EXERCICIOS_POR_FICHAS);
    fichas[quantidade_fichas].numero_de_exercicios = quantidade_exercicios;
}

// Função para Verificar a data
void insira_verifica_data(int *dia, int *mes, int *ano, char info_mensagem[]) 
{
    int data_valida = 0; // Variável com objetivo de saber se a data é valida ou não se for = 1 quer dizer que a data é valida
    int dias_no_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (!data_valida) {
        printf("%s", info_mensagem);
        scanf("%d %d %d", dia, mes, ano);

        if ((*ano % 4 == 0 && *ano % 100 != 0) || (*ano % 400 == 0)) {
            dias_no_mes[1] = 29; // Atualiza fevereiro para 29 dias se for um ano bissexto
        } else {
            dias_no_mes[1] = 28; // Volta a ser 28 em anos não bissextos
        }

        if (*mes < 1 || *mes > 12) {
            printf("Mês inválido. Insira novamente.\n");
        } else if (*dia < 1 || *dia > dias_no_mes[*mes - 1]) {
            printf("Dia inválido para o mês %d. Insira novamente.\n", *mes);
        } else if (*ano < 1) {
            printf("Ano inválido. Insira novamente.\n");
        } else {
            printf("Data válida inserida: %02d/%02d/%04d\n", *dia, *mes, *ano);
            data_valida = 1; 
        }
    }
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

//Função Para verificar o id da ficha
int insira_verifica_id_ficha(t_ficha_de_exercicios fichas[], int quantidade_fichas) 
{
    int id_da_ficha;
    int id_valido = 0; 

    while (!id_valido) {
        printf("Insira o ID da ficha: ");
        scanf("%d", &id_da_ficha);

        id_valido = 1; 
        for (int i = 0; i < quantidade_fichas; i++) {
            if (fichas[i].id_unico_ficha == id_da_ficha) {
                printf("O ID da ficha já existe. Insira outro.\n");
                id_valido = 0; 
                break;
            }
        }
    }
    return id_da_ficha; 
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

    int tipo;
    do
    {
        printf("\n Qual é o tipo de Solução?");
        printf("(1) Algoritmo");
        printf("(2) Código");
        printf("Opção -->: ");
        scanf("%d", &tipo);
    } while (tipo != 1 && tipo != 2);

    if (tipo == 1)
    {
        strcpy(solucao, "Algoritmo");
    }

    if (tipo == 2)
    {
        strcpy(solucao, "Código");
    }
}

// Função para ver os dados dos exercicios
void ver_dados_exercicios(t_exercicio exercicios[], int id_exercicios){

    printf("\nId do exercicio %d:\n", exercicios[id_exercicios].id_unico_exercicio);
    printf("Nome do exericio: %d\n", exercicios[id_exercicios].nome_do_exercicio);
    printf("Dificuldade: %s\n", exercicios[id_exercicios].dificuldade);
    printf("Solução: %s\n", exercicios[id_exercicios].tipo_solucao);
    printf("Id da ficha: %s\n", exercicios[id_exercicios].id_ficha);
}



//GUARDAMENTO DE DADOS

//Guarda a informaçao dos estudantes para um ficheiro
void guardar_estudantes(t_estudante alunos[], int quantidade_alunos, const char* filename) {
    FILE* file = fopen(filename, "w");  // Open file in write mode
    if (file == NULL) {
        printf("Houve problema ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade_alunos; i++) {
        fprintf(file, "%d,%d,%s,%s\n", alunos[i].id_unico_estudante,
                alunos[i].numero_do_estudante,
                alunos[i].nome_do_estudante,
                alunos[i].email_do_estudante);
    }

    fclose(file);  // Close the file after writing
}

//
void guardar_fichas(t_ficha_de_exercicios fichas[], int quantidade_fichas, const char* filename) {
    FILE* file = fopen(filename, "w");  // Open file in write mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade_fichas; i++) {
        fprintf(file, "%d,%s,%d,%d,%d/%d/%d\n", fichas[i].id_unico_ficha,
                fichas[i].nome_da_ficha,
                fichas[i].numero_de_exercicios,
                fichas[i].exercicios_guardados,
                fichas[i].data_de_publicacao.dia,
                fichas[i].data_de_publicacao.mes,
                fichas[i].data_de_publicacao.ano);
    }

    fclose(file);  // Close the file after writing
}

//
void guardar_exercicios(t_exercicio exercicios[], int quantidade_exercicios, const char* filename) {
    FILE* file = fopen(filename, "w");  // Open file in write mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < quantidade_exercicios; i++) {
        fprintf(file, "%d,%s,%s,%s,%d\n", exercicios[i].id_unico_exercicio,
                exercicios[i].nome_do_exercicio,
                exercicios[i].dificuldade,
                exercicios[i].tipo_solucao,
                exercicios[i].id_ficha.id_unico_ficha);
    }

    fclose(file);  // Close the file after writing
}

//Guarda a quantidade de dados de todos
void guardar_todos_dados(t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas, t_exercicio exercicios[], int quantidade_exercicios) {
    guardar_estudantes(alunos, quantidade_alunos, "estudantes.txt");
    guardar_fichas(fichas, quantidade_fichas, "fichas.txt");
    guardar_exercicios(exercicios, quantidade_exercicios, "exercicios.txt");
}


//LOADING DE DADOS
// Load students from a file
int load_estudantes(t_estudante alunos[], const char* filename) {
    FILE* file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^\n]\n", &alunos[i].id_unico_estudante,
                  &alunos[i].numero_do_estudante,
                  alunos[i].nome_do_estudante,
                  alunos[i].email_do_estudante) != EOF) {
        i++;
    }

    fclose(file);  // Close the file after reading
    return i;  // Return the number of students loaded
}

// Load exercise sheets from a file
int load_fichas(t_ficha_de_exercicios fichas[], const char* filename) {
    FILE* file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%d,%[^,],%d,%d,%d/%d/%d\n", &fichas[i].id_unico_ficha,
                  fichas[i].nome_da_ficha,
                  &fichas[i].numero_de_exercicios,
                  &fichas[i].exercicios_guardados,
                  &fichas[i].data_de_publicacao.dia,
                  &fichas[i].data_de_publicacao.mes,
                  &fichas[i].data_de_publicacao.ano) != EOF) {
        i++;
    }

    fclose(file);  // Close the file after reading
    return i;  // Return the number of exercise sheets loaded
}

// Load exercises from a file
int load_exercicios(t_exercicio exercicios[], const char* filename) {
    FILE* file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int i = 0;
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &exercicios[i].id_unico_exercicio,
                  exercicios[i].nome_do_exercicio,
                  exercicios[i].dificuldade,
                  exercicios[i].tipo_solucao,
                  &exercicios[i].id_ficha.id_unico_ficha) != EOF) {
        i++;
    }

    fclose(file);  // Close the file after reading
    return i;  // Return the number of exercises loaded
}

// Load all data (students, exercise sheets, exercises)
void load_todos_dados(t_estudante alunos[], t_ficha_de_exercicios fichas[], t_exercicio exercicios[]) {
    int quantidade_alunos = load_estudantes(alunos, "estudantes.txt");
    int quantidade_fichas = load_fichas(fichas, "fichas.txt");
    int quantidade_exercicios = load_exercicios(exercicios, "exercicios.txt");

    printf("Carregamento concluído:\n");
    printf("Estudantes carregados: %d\n", quantidade_alunos);
    printf("Fichas carregadas: %d\n", quantidade_fichas);
    printf("Exercícios carregados: %d\n", quantidade_exercicios);
}