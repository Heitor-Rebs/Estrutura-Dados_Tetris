#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Definindo o número máximo de peças na fila */
#define max_peca 5
#define max_reserva 3

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

/* Criando estrutura da pilha */
struct Pilha
{
    struct Peca pecas[max_reserva];
    int topo;
    int totalPecasReservadas;
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

void iniciarPilha(struct Pilha *p)
{
    p->topo = -1;
    p->totalPecasReservadas = 0;
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

/* Função para mostrar as peças da pilha */
void mostrarPilha (struct Pilha *p)
{
    if (p->totalPecasReservadas == 0)
    {
        printf("Reserva vazia!\n");
        return;
    }
    int i = 0;
    printf("\Reserva:\n");
    for (i = p->topo; i >= 0; i--) {
        printf("[%s, %d]\n", p->pecas[i].nome, p->pecas[i].id);
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
void inserirPeca(struct Fila *f, struct Pilha *p, int *totalCadastro)
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
}

/* Função para jogar peça da fila */
void jogarPeca(struct Fila *f, struct Pilha *p,int *totalCadastro)
{
    if (f->totalPecas == 0)
    {
        printf("Fila vazia!\n");
        return;
    }
    (*totalCadastro)--;
    f->inicio = (f->inicio + 1) % max_peca;
    f->totalPecas--;
    inserirPeca(f, p, totalCadastro);
    mostrarPilha(p);
    mostrarFila(f);
}

/* Função para mover peça para reserva */
void reservarPeca(struct Pilha *p, struct Fila *f, int *totalCadastro)
{
    if(f->totalPecas == 0)
    {
        printf("Fila vazia!\n");
        return;
    }
    if(p->totalPecasReservadas == 3)
    {
        printf("\nReserva cheia!\n");
        return;
    }

    p->topo++;
    p->pecas[p->topo] = f->pecas[f->inicio];
    p->totalPecasReservadas++;
    (*totalCadastro)--;
    f->inicio = (f->inicio + 1) % max_peca;
    f->totalPecas--;
    inserirPeca(f, p, totalCadastro);
    mostrarPilha(p);
    mostrarFila(f);
}

/* Função para jogar peça da reserva */
void usarReserva(struct Pilha *p, struct Fila *f)
{
    if(p->totalPecasReservadas == 0)
    {
        printf("\nReserva vazia!\n");
        return;
    }

    p->topo--;
    p->totalPecasReservadas--;

    mostrarPilha(p);
    mostrarFila(f);
}

/* Função trocar peça da fila pela peça da pilha */
void trocarPeca(struct Pilha *p, struct Fila *f)
{
    if(p->totalPecasReservadas == 0)
    {
        printf("\nReserva vazia!\n");
        return;
    }

    struct Peca e;
    e = p->pecas[p->topo];
    p->pecas[p->topo] = f->pecas[f->inicio];
    f->pecas[f->inicio] = e;
    mostrarPilha(p);
    mostrarFila(f);
}

/* Função para trocar as três peças da reserva para a fila */
void trocaMultipla(struct Pilha *p, struct Fila *f)
{
    if(p->totalPecasReservadas < 3)
    {
        printf("\nReserva com poucos elementos!\n");
        return;
    }

    struct Peca e[max_reserva];
    int i;
    for(i=0;i<3;i++)
    {
        e[i] = p->pecas[(p->topo)-i];
        p->pecas[(p->topo)-i] = f->pecas[((f->inicio)+2-i) % max_peca];

    }
    for(i=0;i<3;i++)
    {
        f->pecas[(f->inicio+i) % max_peca] = e[i];
    }
    mostrarPilha(p);
    mostrarFila(f);
}

int main()
{
    struct Fila fila;
    struct Pilha pilha;
    int opcao, i = 0;
    int totalCadastro = 0;

    iniciarFila(&fila);
    iniciarPilha(&pilha);

    /* Inicar jogo com 5 peças na fila */
    for(i = 0;i < 5;i++)
    {
        inserirPeca(&fila, &pilha, &totalCadastro);
    }
    mostrarFila(&fila);

    /* Montando menu de Interação com o inventário */
    do
    {
        opcao = 0;
        printf("\n----Menu de Interacao----\n\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        limparbuffer();

        switch (opcao)
        {
        case 1:
            jogarPeca(&fila, &pilha, &totalCadastro);
            break;
        case 2:
            reservarPeca(&pilha,&fila,&totalCadastro);
            break;
        case 3:
            usarReserva(&pilha, &fila);
            break;
        case 4:
            trocarPeca(&pilha, &fila);
            break;
        case 5:
            trocaMultipla(&pilha, &fila);
            break;
        case 0:
            printf("\nSaindo...!\n");
            break;
        }
    }while(opcao!=0);
}


