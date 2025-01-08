#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TAMANHO_STRING_LONGA 80
#define MAXIMO_EXERCICIOS 100
#define TAMANHO_STRING_CURTA 20
#define MAXIMO_ESTUDANTES 100
#define MAXIMO_EXERCICIOS_POR_FICHAS 10
#define MAXIMO_FICHAS 10
#define MAXIMO_SUBMISSOES 100

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

typedef struct {
    int id_unico_submissao;        
    int id_estudante;              
    int id_ficha;                  
    int id_exercicio;              
    t_data data_submissao;
    int numero_linhas_solucao;     
    int classificacao_obtida;      //clsassificacao [0, 100]
} t_submissao;

// Funções dados estudantes
int inserir_dados_estudantes(t_estudante alunos[], int *quantidade_alunos);
int verifica_numero_estudante(t_estudante alunos[], int *quantidade_alunos);
int verifica_existencia_id_estudante(int id, t_estudante alunos[], int total_de_estudantes, int estudante_verificado);
void ver_dados_estudantes(t_estudante alunos[], int *quantidade_alunos);

// Funções dados fichas
int inserir_dados_fichas(t_ficha_de_exercicios fichas[], int *quantidade_fichas);
void insira_verifica_nome_ficha(char pedido_de_informacao[], t_ficha_de_exercicios fichas[], int *quantidade_fichas);
void insira_verifica_exercicios_da_ficha(char pedido_informacao[], t_ficha_de_exercicios fichas[], int quantidade_fichas);
void insira_verifica_data(int *dia, int *mes, int *ano, char info_mensagem[]);    
void ver_dados_fichas(t_ficha_de_exercicios fichas[], int quantidade_fichas);

// Funções dados exercícios
int inserir_dados_exercicios(t_exercicio exercicios[], int *quantidade_exercicios, t_ficha_de_exercicios fichas[], int *quantidade_fichas);
int insira_verifica_id_ficha(t_ficha_de_exercicios fichas[], int *quantidade_fichas);
void ler_dificuldade_exercicio(char classificacao[]);
void ler_tipo_solucao_exercicio(char solucao[]);
void verifica_existencia_id_exercicios(t_exercicio exercicios[], int *quantidade_exercicios, int id_exercicio, int *exercicio_confirmado);
void ver_dados_exercicios(t_exercicio exercicios[], int id_exercicios);

//Funções Submissoes
void inserir_submissao(t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas, t_exercicio exercicios[], int quantidade_exercicios, t_submissao submissoes[], int quantidade_submissoes);
void exibir_submissoes(t_submissao submissoes[], int quantidade_submissoes);
void ObterDadosExercicios(t_exercicio exercicios[], int *quantidade_exercicios, t_submissao *nova_submissao);
void ObterDadosFicha(t_ficha_de_exercicios fichas[], int *quantidade_fichas, t_submissao *nova_submissao);
void ObterDadosEstudante(t_estudante alunos[], int *quantidade_alunos, t_submissao *nova_submissao);
t_submissao submissoes[MAXIMO_SUBMISSOES];

//ESTATISTICAS
void total_submissoes_por_aluno(t_submissao submissoes[], int quantidade_submissoes, t_estudante alunos[], int quantidade_alunos);
float media_classificacoes_nas_submissoes_por_estudante(t_submissao submissoes[], int quantidade_submissoes, int id_estudante);


// Faltam as Funções relacionadass com os ficheiros
//GUARDAR INFORMAÇOES EM FICHEIROS
void guardar_estudantes(t_estudante alunos[], int *quantidade_alunos, const char* filename);
void guardar_fichas(t_ficha_de_exercicios fichas[], int *quantidade_fichas, const char* filename);
void guardar_exercicios(t_exercicio exercicios[], int *quantidade_exercicios, const char* filename);
void guardar_todos_dados(t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas, t_exercicio exercicios[], int quantidade_exercicios, t_submissao submissoes[], int quantidade_submissoes);

//DAR LOAD à DATA dos ficheiros
int load_estudantes(t_estudante alunos[], const char* filename);
int load_fichas(t_ficha_de_exercicios fichas[], const char* filename);
int load_exercicios(t_exercicio exercicios[], const char* filename);
void load_todos_dados(t_estudante alunos[], t_ficha_de_exercicios fichas[], t_exercicio exercicios[], int *quantidade_alunos, int *quantidade_fichas, int *quantidade_exercicios);


//MENU
void menuPrincipal(t_estudante alunos[], int *quantidade_alunos, t_ficha_de_exercicios fichas[], int *quantidade_fichas, t_exercicio exercicios[], int *quantidade_exercicios, t_submissao submissoes[], int *quantidade_submissoes);
char confirmarSair(void);





//FUNCAO MAIN
int main() 
{
    t_estudante alunos[MAXIMO_ESTUDANTES];
    t_ficha_de_exercicios fichas[MAXIMO_FICHAS];
    t_exercicio exercicios[MAXIMO_EXERCICIOS];
    t_submissao submissoes[MAXIMO_SUBMISSOES];
    
    int quantidade_alunos = 0;
    int quantidade_fichas = 0;
    int quantidade_exercicios = 0;
    int quantidade_submissoes = 0;

  
    load_todos_dados(alunos, fichas, exercicios, &quantidade_alunos, &quantidade_fichas, &quantidade_exercicios);

  
    menuPrincipal(alunos, &quantidade_alunos, fichas, &quantidade_fichas, exercicios, &quantidade_exercicios, submissoes, &quantidade_submissoes);

    
    guardar_todos_dados(alunos, quantidade_alunos, fichas, quantidade_fichas, exercicios, quantidade_exercicios, submissoes, quantidade_submissoes);

    return 0; 
}





// Funções dados estudantes
// Função para ler os dados dos estudantess
int inserir_dados_estudantes(t_estudante alunos[], int *quantidade_alunos)
{
    t_estudante Estudante;
    Estudante.id_unico_estudante = *quantidade_alunos + 1;

    printf("Numero do Estudante: ");
    scanf("%d", &Estudante.numero_do_estudante);

    printf("Nome do Estudante: ");
    scanf(" %[^\n]s", Estudante.nome_do_estudante);

    printf("Email do Estudante: ");
    scanf(" %[^\n]s", Estudante.email_do_estudante);  // [^\n] , o ^ condição de negação , ou seja, enquanto nao houver mudança de linha pode se continuar a escrever até o tamanho max da string

    alunos[*quantidade_alunos] = Estudante;

    return *quantidade_alunos + 1; // incrementação dos estudantes
}

//verificação do numero do estudante
int verifica_numero_estudante(t_estudante alunos[], int *quantidade_alunos) 
{
    int indice;
    int numeroEstudante;
    printf("Insira o numero do estudante a verificar: ");
    scanf("%d", &numeroEstudante);

    for (int indice; indice < *quantidade_alunos; indice++) 
    {
        if (alunos[indice].numero_do_estudante == numeroEstudante) 
        {
            printf("O numero de estudante já existe.\n");
        }else 
        {
            printf("O numero do estudante não existe.\n");
        }
    }
}


//verificar se o id do estudante existe
int verifica_existencia_id_estudante(int id, t_estudante alunos[], int total_de_estudantes) 
{
    for (int indi = 0; indi < total_de_estudantes; indi++) 
    {
        if (alunos[indi].id_unico_estudante == id) 
        {
            return 1;
        }
    }
    return 0; 
}


// Função para ver os dados dos Estudantes
void ver_dados_estudantes(t_estudante alunos[], int *quantidade_alunos)
{
    // podemos fazer-validação do id    
    printf("\nLista de Estudantes :\n");
    int indi = 0;

    for (indi; indi < *quantidade_alunos; indi++)
    {
        printf("\nID: %d\n", alunos[indi].id_unico_estudante);
        printf("\nNumero: %d\n",alunos[indi].numero_do_estudante);
        printf("\nNome: %s",alunos[indi].nome_do_estudante);
        printf("\nEmail: %s\n",alunos[indi].email_do_estudante);
    }

}



// Funções dados fichas
// Função para Inserir os dados das Fichas
int inserir_dados_fichas(t_ficha_de_exercicios fichas[], int *quantidade_fichas)
{
    t_ficha_de_exercicios FichaExercicios;
    FichaExercicios.id_unico_ficha = *quantidade_fichas + 1;

    printf("Nome da Ficha: ");
    scanf(" %[^\n]s", FichaExercicios.nome_da_ficha);

    printf("Numero de Exercicios: ");
    scanf("%d", FichaExercicios.numero_de_exercicios);

    printf("Data de Publicação: ");
    scanf("%d", &FichaExercicios.data_de_publicacao);

    fichas[*quantidade_fichas] = FichaExercicios;

    return *quantidade_fichas + 1;
}

//Função com objetivo verificar se ja existe uma ficha com o mesmo nome
void insira_verifica_nome_ficha(char pedido_de_informacao[], t_ficha_de_exercicios fichas[], int *quantidade_fichas){

    int indice, existencia;

    do {
        existencia =0;

        printf("%s", pedido_de_informacao);
        getchar();
        fgets(fichas[*quantidade_fichas].nome_da_ficha, TAMANHO_STRING_LONGA, stdin);
        fichas[*quantidade_fichas].nome_da_ficha[strcspn(fichas[*quantidade_fichas].nome_da_ficha, "\n")] =0;
        
        for (int indice=0; indice < *quantidade_fichas; indice++){

            if(strcmp(fichas[indice].nome_da_ficha, fichas[*quantidade_fichas].nome_da_ficha) == 0){

                existencia =1;
                printf("O nome desta ficha já existe!!\n");
            }
        }
    } while (existencia);
}


//Função com objetivo de verificar se o numero de exercicios excedeu o limite por ficha
void insira_verifica_exercicios_da_ficha(char pedido_informacao[], t_ficha_de_exercicios fichas[], int *quantidade_fichas){

    int quantidade_exercicios = 0;

    do {
        printf("%s", pedido_informacao);
        scanf("%d", &quantidade_exercicios);
        if (quantidade_exercicios <1 || quantidade_exercicios > MAXIMO_EXERCICIOS_POR_FICHAS)
        {
            printf("O numero de exercicios excedeu o limite por ficha (1- %d)!!\n", MAXIMO_EXERCICIOS_POR_FICHAS);
        }      
    } while (quantidade_exercicios < 1 || quantidade_exercicios > MAXIMO_EXERCICIOS_POR_FICHAS);
    fichas[*quantidade_fichas].numero_de_exercicios = quantidade_exercicios;
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
void ver_dados_fichas(t_ficha_de_exercicios fichas[], int *quantidade_fichas)
{
    int indi = 0;
    printf("\n Lista de Fichas de Exercícios :\n");
    for (indi; indi < *quantidade_fichas; indi++)
    // podemos fazer-validação do id
    printf("\nID Ficha %d:\n", fichas[indi].id_unico_ficha);
    printf("Numero: %d\n", fichas[indi].numero_de_exercicios);
    printf("Nome: %s\n", fichas[indi].nome_da_ficha);
    printf("Data: %s\n", fichas[indi].data_de_publicacao);
}




// Funções dados exercícios

// Função para inserir os dados dos exercicios
int inserir_dados_exercicios(t_exercicio exercicios[], int *quantidade_exercicios, t_ficha_de_exercicios fichas[], int *quantidade_fichas)
{
    if (*quantidade_exercicios >= MAXIMO_EXERCICIOS)
    {
        printf("A quantidade máxima de exercicios foi atingida\n");
    }
    else
    {
        exercicios[*quantidade_exercicios].id_unico_exercicio = *quantidade_exercicios + 1;
        exercicios[*quantidade_exercicios].id_ficha.id_unico_ficha; //preciso e criar a função = insira_verifica_id_ficha_exericios(fichas, quantidade_Fichas);

        printf("Escreva o nome do Exercicio");
        getchar();
        fgets(exercicios[*quantidade_exercicios].nome_do_exercicio, TAMANHO_STRING_LONGA, stdin);
        exercicios[*quantidade_exercicios].nome_do_exercicio[strcspn(exercicios[*quantidade_exercicios].nome_do_exercicio, "\n")] = 0;

        ler_dificuldade_exercicio(exercicios[*quantidade_exercicios].dificuldade);

        ler_tipo_solucao_exercicio(exercicios[*quantidade_exercicios].tipo_solucao);
        quantidade_exercicios = quantidade_exercicios + 1;
    }
    return *quantidade_exercicios;
}

//Função Para verificar o id da ficha
int insira_verifica_id_ficha(t_ficha_de_exercicios fichas[], int *quantidade_fichas) 
{
    int id_da_ficha;
    int id_valido;

    do {
        printf("Insira o ID da ficha: ");
        scanf("%d", &id_da_ficha);

        id_valido = 1; 
        for (int i = 0; i < *quantidade_fichas; i++) {
            if (fichas[i].id_unico_ficha == id_da_ficha) {
                printf("O ID da ficha já existe. Insira outro.\n");
                id_valido = 0; 
            }
        }
    } while (id_valido == 0); 

    return id_da_ficha; 
}


// Função para ler a Dificuldade da ficha
void ler_dificuldade_exercicio(char classificacao[])
{

    int dificuldade;
    do
    {
        printf("\n Qual é a dificuldade do Exercicio:");
        printf("\n(1) Baixo");
        printf("\n(2) Medio");
        printf("\n(3) Elevado");
        printf("\nOpção -->: ");
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
        printf("\n(1) Algoritmo");
        printf("\n(2) Código");
        printf("\nOpção -->: ");
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

// Função para verificar a existência de um ID de exercício
void verifica_existencia_id_exercicios(t_exercicio exercicios[], int *quantidade_exercicios, int id_exercicio, int *exercicio_confirmado) 
{
    int i = 0;
    *exercicio_confirmado = 0;
    for (i; i < *quantidade_exercicios; i++) 
    {
        if (exercicios[i].id_unico_exercicio == id_exercicio) {
            *exercicio_confirmado =1;
            printf("O ID do exercício %d já existe!\n", id_exercicio);
 
        }
    }
    printf("O ID do exercício %d é válido.\n", id_exercicio); // Caso não exista, ID é válido
}

// Função para ver os dados dos exercicios
void ver_dados_exercicios(t_exercicio exercicios[], int *quantidade_exercicios)
{
    int indi = 0;
    printf("\nLista de Exercícios:\n");
    
    // Loop através de todos os exercícios
    for (indi = 0; indi < *quantidade_exercicios; indi++)
    {
        printf("\nID do Exercicio: %d\n", exercicios[indi].id_unico_exercicio);
        printf("Nome do Exercício: %s\n", exercicios[indi].nome_do_exercicio);
        printf("Dificuldade: %s\n", exercicios[indi].dificuldade);
        printf("Solução: %s\n", exercicios[indi].tipo_solucao);
        printf("ID da Ficha: %d\n", exercicios[indi].id_ficha.id_unico_ficha);
    }
}



//FUNCOES DE SUBMISSOES
void inserir_submissao(t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas, t_exercicio exercicios[], int quantidade_exercicios, t_submissao submissoes[], int *quantidade_submissoes) {
    t_submissao nova_submissao;
    int estudante_verificado = 0, exercicio_confirmado = 0;

    nova_submissao.id_unico_submissao = *quantidade_submissoes + 1;


    // Obter dados do estudante
    printf("Digite o ID do estudante (id_unico_estudante): ");
    scanf("%d", &nova_submissao.id_estudante);
    
    // Verifica se o estudante existe enquanto está submeter-se
    if (!verifica_existencia_id_estudante(nova_submissao.id_estudante, alunos, quantidade_alunos)) {
        printf("Estudante inválido! A submissão não foi registada.\n");
        return;
    }

    // Obter dados da ficha
    printf("Digite o ID da ficha de exercícios (id_unico_ficha): ");
    scanf("%d", &nova_submissao.id_ficha);

    // Verifica se a ficha existe
    nova_submissao.id_ficha = insira_verifica_id_ficha(fichas, &quantidade_fichas);
    if (nova_submissao.id_ficha == 0) {
        printf("Ficha inválida! A submissão não foi registada.\n");
        return;
    }

    // Obter dados do exercício
    printf("Digite o ID do exercício (id_unico_exercicio): ");
    scanf("%d", &nova_submissao.id_exercicio);
    
    // Verifica se o exercício existe
    verifica_existencia_id_exercicios(exercicios, &quantidade_exercicios, nova_submissao.id_exercicio, &exercicio_confirmado);
    if (!exercicio_confirmado) {
        printf("Exercício não encontrado.\n");
        return;
    }

    // Input de Data
    printf("Digite a data de submissão (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &nova_submissao.data_submissao.dia,
          &nova_submissao.data_submissao.mes,
          &nova_submissao.data_submissao.ano);

    // Número de linhas da solução
    printf("Digite o número de linhas da solução: ");
    scanf("%d", &nova_submissao.numero_linhas_solucao);

    // Classificação
    printf("Digite a classificação obtida (0-100): ");
    scanf("%d", &nova_submissao.classificacao_obtida);

    //guarda num array
    submissoes[*quantidade_submissoes] = nova_submissao;
    (*quantidade_submissoes)++;

    printf("Submissão registrada com sucesso!\n");
}


void ObterDadosEstudante(t_estudante alunos[], int *quantidade_alunos, t_submissao *nova_submissao) {
    
    printf("Digite o ID do estudante (id_unico_estudante): ");
    
    
    if (scanf("%d", &(*nova_submissao).id_estudante) != 1) {
        printf("ID inválido! Por favor insira um número inteiro.\n");

        while (getchar() != '\n'); 
        return;
    }

    if (!verifica_existencia_id_estudante((*nova_submissao).id_estudante, alunos, *quantidade_alunos)) {
        printf("Estudante inválido! A submissão não foi registada.\n");
        return;
    }

    // If the student is valid, the submission ID will be set.
    printf("Estudante validado com sucesso!\n");
}

void ObterDadosFicha(t_ficha_de_exercicios fichas[], int *quantidade_fichas, t_submissao *nova_submissao) {
    printf("Digite o ID da ficha de exercícios (id_unico_ficha): ");
    scanf("%d", &(*nova_submissao).id_ficha);

    //Verifica se a ficha existe
    (*nova_submissao).id_ficha = insira_verifica_id_ficha(fichas, quantidade_fichas);
    if ((*nova_submissao).id_ficha ==0 ){
        printf ("Ficha inválida");
    }
}

void ObterDadosExercicios(t_exercicio exercicios[], int *quantidade_exercicios, t_submissao *nova_submissao){
    int exercicio_confirmado = 0;

    printf("Digite o ID do exercício (id_unico_exercicio): ");
    scanf("%d", &(*nova_submissao).id_exercicio);
    // Verifica se exercicio existe
    verifica_existencia_id_exercicios(exercicios, quantidade_exercicios, (*nova_submissao).id_exercicio, &exercicio_confirmado);
    
    if (!exercicio_confirmado)
    {
    printf("Exercício não encontrado.\n");
    return; 
    }
}


//VER SUBMISSOES
void exibir_submissoes(t_submissao submissoes[], int quantidade_submissoes) {
    if (quantidade_submissoes == 0) {
        printf("Nenhuma submissão registrada.\n");
        return;
    }

    int i = 0;

    printf("\nSubmissões:\n");
    for (i; i < quantidade_submissoes; i++) {
        printf("ID Submissao: %d\n", submissoes[i].id_unico_submissao);
        printf("ID Estudante: %d\n", submissoes[i].id_estudante);
        printf("ID Ficha: %d\n", submissoes[i].id_ficha);
        printf("ID Exercicio: %d\n", submissoes[i].id_exercicio);
        printf("Data de Submissão: %02d/%02d/%04d\n", submissoes[i].data_submissao.dia,
                                                     submissoes[i].data_submissao.mes,
                                                     submissoes[i].data_submissao.ano);
        printf("Número de Linhas da Solução: %d\n", submissoes[i].numero_linhas_solucao);
        printf("Classificação Obtida: %d\n\n", submissoes[i].classificacao_obtida);
    }
}



//Estatisticas
//Total de submissoes por aluno
void total_submissoes_por_aluno(const t_submissao submissoes[], int quantidade_submissoes, t_estudante alunos[], int quantidade_alunos)
{
    int indice_alunos, indice_submissao, total;

    for (indice_alunos = 0; indice_alunos < quantidade_alunos; indice_alunos++)
    {
        total = 0;
        for (indice_submissao = 0; indice_submissao < quantidade_submissoes; indice_submissao++)
        {
            if (submissoes[indice_submissao].id_estudante == alunos[indice_alunos].id_unico_estudante)
            {
                total = total + 1;
            }
        }

        printf("\nO Estudante %s fez um total de submissoes : %d \n ",alunos[indice_alunos].id_unico_estudante, total);
    }
}

//media das classificacoes 
float media_classificacoes_nas_submissoes_por_estudante(t_submissao submissoes[], int quantidade_submissoes, int id_estudante)
{
    int indice = 0, contador = 0, soma_das_notas = 0;
    float media = 0;
    for (indice = 0; indice < quantidade_submissoes; indice++)
    {
        if (submissoes[indice].id_estudante == id_estudante)
        {
            contador = contador + 1;
            soma_das_notas = soma_das_notas + submissoes[indice].classificacao_obtida;
        }
    }
    if (contador > 0)
    {
        media = (float)soma_das_notas / contador;
    } else {
        printf("O estundate ainda não tem submissões.\n");
    }
}

//funcao para calcular a percentagem dos exercicios por ficha
void porcentagem_exercicios_resolvidos_por_ficha(t_submissao submissoes[], int quantidade_submissoes, t_estudante alunos[], int quantidade_alunos, t_ficha_de_exercicios fichas[], int quantidade_fichas)
{
    int indice_alunos, indice_submissao, indice_ficha, exercicios_resolvidos, total_exercicios;
    float porcentagem;

    // ciclo for para cada aluno
    for (indice_alunos = 0; indice_alunos < quantidade_alunos; indice_alunos++)
    {
        printf("\nAluno: %s\n", alunos[indice_alunos].nome_do_estudante);
        
        // ciclo for para cada ficha de exercícios
        for (indice_ficha = 0; indice_ficha < quantidade_fichas; indice_ficha++)
        {
            exercicios_resolvidos = 0;
            total_exercicios = fichas[indice_ficha].numero_de_exercicios;

            // ciclpo for para ver o numero de exercicios feito
            for (indice_submissao = 0; indice_submissao < quantidade_submissoes; indice_submissao++)
            {
                // verifica o aluno com a ficha
                if (submissoes[indice_submissao].id_estudante == alunos[indice_alunos].id_unico_estudante &&
                    submissoes[indice_submissao].id_ficha == fichas[indice_ficha].id_unico_ficha)
                {
                    exercicios_resolvidos++;
                }
            }

            // Calcular a porcentagem dos exercecios feitos
            if (total_exercicios > 0)
            {
                porcentagem = ((float)exercicios_resolvidos / total_exercicios) * 100;
                printf("Ficha: %s - %d/%d exercícios resolvidos (%.2f%%)\n",
                       fichas[indice_ficha].nome_da_ficha,
                       exercicios_resolvidos,
                       total_exercicios,
                       porcentagem);
            }
            else
            {
                printf("Ficha: %s - Nenhum exercício na ficha.\n", fichas[indice_ficha].nome_da_ficha);
            }
        }
    }
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

    int contador = 0;
    while (fscanf(file, "%d,%d,%[^,],%[^\n]\n", &alunos[contador].id_unico_estudante,
                  &alunos[contador].numero_do_estudante,
                  alunos[contador].nome_do_estudante,
                  alunos[contador].email_do_estudante) != EOF) {
        contador++;
    }

    fclose(file);  // Close the file after reading
    return contador;  // Return the number of students loaded
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
void load_todos_dados(t_estudante alunos[], t_ficha_de_exercicios fichas[], t_exercicio exercicios[], int *quantidade_alunos, int *quantidade_fichas, int *quantidade_exercicios) {
    *quantidade_alunos = load_estudantes(alunos, "estudantes.txt");
    *quantidade_fichas = load_fichas(fichas, "fichas.txt");
    *quantidade_exercicios = load_exercicios(exercicios, "exercicios.txt");

    printf("Carregamento concluído:\n");
    printf("Estudantes carregados: %d\n", *quantidade_alunos);
    printf("Fichas carregadas: %d\n", *quantidade_fichas);
    printf("Exercícios carregados: %d\n", *quantidade_exercicios);
}


//MENYPRINCIPAL
void menuPrincipal(t_estudante alunos[], int *quantidade_alunos, t_ficha_de_exercicios fichas[], int *quantidade_fichas, t_exercicio exercicios[], int *quantidade_exercicios, t_submissao submissoes[], int *quantidade_submissoes)
{
    int opcao;

    do
    {
        printf("\n****** Menu Principal ******\n");
        printf("1. Inserir Dados Estudante\n");
        printf("2. Ver Dados Estudantes\n");
        printf("3. Inserir Ficha de Exercícios\n");
        printf("4. Ver Fichas de Exercícios\n");
        printf("5. Inserir Exercicio\n");
        printf("6. Ver Exercicios\n");
        printf("7. Inserir Submissao\n");
        printf("8. Exibir Submissoes\n");
        printf("9. Guardar Dados\n");
        printf("10. Salvar Dados\n");
        printf("11. Carregar Dados\n");
        printf("12. Menu Estatisticas\n");
        printf("0. Sair\n");
        printf("Opcao ->  ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserir_dados_estudantes(alunos, quantidade_alunos);
            break;
        case 2:
            ver_dados_estudantes(alunos, quantidade_alunos);
            break;
        case 3:
            inserir_dados_fichas(fichas, quantidade_fichas);
            break;
        case 4:
            ver_dados_fichas(fichas, quantidade_fichas);
            break;
        case 5:
            inserir_dados_exercicios(exercicios, quantidade_exercicios, fichas , quantidade_fichas);
            break;
        case 6:
            ver_dados_exercicios(exercicios, quantidade_exercicios);
            break;
        case 7:
            inserir_submissao(alunos, *quantidade_alunos, fichas, *quantidade_fichas, exercicios, *quantidade_exercicios, submissoes, quantidade_submissoes);
            break;
        case 8:
            exibir_submissoes(submissoes, *quantidade_submissoes);
            break;
        case 9:
            guardar_estudantes(alunos, *quantidade_alunos, "estudantes.txt");
            break;
        case 10:
            guardar_fichas(fichas, *quantidade_fichas, "fichas.txt");
            break;
        case 11:
            load_todos_dados(alunos, fichas,  exercicios, quantidade_alunos, quantidade_fichas, quantidade_exercicios);
            break;
        case 0:
            printf("A sair do programa...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);
}

//CONFIRMAR SAIDA
char confirmarSair(void)
{
    char sair;
    do
    {
        printf("Tem a certeza que quer sair? Sim(S) Nao(N): ");
        scanf(" %c", &sair);
        sair = toupper(sair);
        if (sair == 'S')
        {
            printf("A sair\n");
            exit(0);
        }
        else if (sair == 'N')
        {
            return 'N';
        }

    } while (sair != 'S' && sair != 'N');

    return sair;
} 