#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Definindo o número máximo de peças na fila */
#define max_peca 5

/* Criando estrutura de cada peça na fila */
struct Peca
{
    char nome[2];
    int id;
};

/* Criando estrutura da fila */
struct Fila
{
    struct Peca pecas[max_peca];
    int inicio;
    int fim;
    int totalPecas;
};

void limparbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

void iniciarFila(struct Fila *f)
{
    f->fim = 0;
    f->inicio = 0;
    f->totalPecas =0;
}

/* Função para mostrar as peças da fila */
void mostrarFila(struct Fila *f){
    if (f->totalPecas == 0)
    {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila: ");
    int i = 0, indice = 0;
    for (i = 0, indice = f->inicio; i < f->totalPecas; i++, indice = (indice + 1) % max_peca) {
        printf("[%s, %d] ", f->pecas[indice].nome, f->pecas[indice].id);
    }
    printf("\n");
}

/* Função para gerar uma peca de formato aleatório */
struct Peca gerarPeca(int *totalCadastro)
{
    int tipoPeca = (rand() % 4) + 1;
    struct Peca novaPeca;
    novaPeca.id = *totalCadastro;
    switch (tipoPeca)
    {
        case 1:
            strcpy(novaPeca.nome, "I");
            break;
        case 2:
            strcpy(novaPeca.nome, "O");
            break;
        case 3:
            strcpy(novaPeca.nome, "T");
            break;
        case 4:
            strcpy(novaPeca.nome, "L");
            break;
    }
    return novaPeca;
}

/* Função para inserir peça na fila */
void inserirPeca(struct Fila *f, int *totalCadastro)
{
    if (f->totalPecas == max_peca)
    {
        printf("Fila cheia!\n");
        return;
    }
    (*totalCadastro)++;
    f->pecas[f->fim] = gerarPeca(totalCadastro);
    f->fim = (f->fim + 1) % max_peca;
    f->totalPecas++;
    mostrarFila(f);
}

/* Função para jogar peça da fila */
void jogarPeca(struct Fila *f,int *totalCadastro)
{
    if (f->totalPecas == 0)
    {
        printf("Fila vazia!\n");
        return;
    }
    (*totalCadastro)--;
    f->inicio = (f->inicio + 1) % max_peca;
    f->totalPecas--;
    mostrarFila(f);
}

int main()
{
    struct Fila fila;
    int opcao;
    int totalCadastro;

    iniciarFila(&fila);

    /* Montando menu de Interação com o inventário */
    do
    {
        opcao = 0;
        printf("\n----Menu de Interacao----\n\n");
        printf("1 - Jogar peca\n");
        printf("2 - Inserir nova peca\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        limparbuffer();

        switch (opcao)
        {
        case 1:
            jogarPeca(&fila, &totalCadastro);
            break;
            break;
        case 2:
            inserirPeca(&fila, &totalCadastro);
            break;
        case 0:
            printf("\nSaindo...!\n");
            break;
        }
    }while(opcao!=0);
}


