#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // tamanho fixo da fila

// Estrutura que representa uma peça
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Função para inicializar a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("A fila está cheia! Não é possível adicionar mais peças.\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->quantidade++;
}

// Remove uma peça da frente da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) {
        printf("A fila está vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->quantidade--;
    return removida;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila de peças vazia.\n");
        return;
    }

    printf("Fila de peças:\n");
    int i;
    int index = f->frente;
    for (i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[index].nome, f->itens[index].id);
        index = (index + 1) % MAX;
    }
    printf("\n\n");
}

int main() {
    Fila fila;
    int opcao;
    int contador = 0; // para gerar ids únicos

    srand(time(NULL)); // semente aleatória

    inicializarFila(&fila);

    // Inicializa com 5 peças
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(contador++));
    }

    do {
        exibirFila(&fila);
        printf("Opções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao) {
            case 1: {
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n\n", jogada.nome, jogada.id);
                }
                break;
            }
            case 2:
                enqueue(&fila, gerarPeca(contador++));
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
