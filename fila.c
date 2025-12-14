#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TAM 50

// ---------- ESTRUTURA DO PEDIDO ----------
typedef struct {
    char nome[20];
    int tempo;
    int pontos;
} Pedido;

// ---------- FILA CIRCULAR ----------
typedef struct {
    Pedido fila[TAM];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// ---------- FUNÇÕES DA FILA ----------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM;
}

void enqueue(Fila *f, Pedido p) {
    if (filaCheia(f)) return;
    f->fila[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->tamanho++;
}

Pedido dequeue(Fila *f) {
    Pedido p = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->tamanho--;
    return p;
}

// ---------- CRIAR PEDIDO ALEATÓRIO ----------
Pedido gerarPedido() {
    Pedido p;
    int r = rand() % 4;

    if (r == 0) {
        strcpy(p.nome, "Hamburguer");
        p.tempo = 3;
        p.pontos = 10;
    } else if (r == 1) {
        strcpy(p.nome, "Pizza");
        p.tempo = 5;
        p.pontos = 20;
    } else if (r == 2) {
        strcpy(p.nome, "Salada");
        p.tempo = 2;
        p.pontos = 5;
    } else {
        strcpy(p.nome, "Massa");
        p.tempo = 4;
        p.pontos = 15;
    }

    return p;
}

// ----------- LIMPAR A TELA -----------
void limparTela() {
    sleep(2);
    system("cls||clear");
}

// ---------- TELA DE LOAD ----------
void prepararPedido() {
    printf("Preparando");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    limparTela();
}

// ---------- MOSTRAR FILA ----------
void mostrarFila(Fila *f) {
    printf("\nPedidos na fila:\n");

    int i = f->inicio;
    for (int c = 0; c < f->tamanho; c++) {
        printf("- %s (tempo %d | pontos %d)\n",
               f->fila[i].nome,
               f->fila[i].tempo,
               f->fila[i].pontos);
        i = (i + 1) % TAM;
    }
}

// ---------- MAIN ----------
int main() {
    srand(time(NULL));

    Fila cozinha;
    inicializarFila(&cozinha);

    int tempoTotal = 10;
    int pontuacao = 0;
    int numPedidos = 5;

    printf("=== JOGO DA COZINHA ===\n");

    // Gerar pedidos iniciais
    for (int i = 0; i < numPedidos; i++) {
        Pedido p = gerarPedido();
        enqueue(&cozinha, p);
        tempoTotal += 2;
    }

    // Loop principal
    while (!filaVazia(&cozinha)) {

        mostrarFila(&cozinha);

        Pedido atual = cozinha.fila[cozinha.inicio];

        printf("\nPedido atual: %s\n", atual.nome);
        printf("Tempo: %d | Pontos: %d\n", atual.tempo, atual.pontos);
        printf("Tempo restante: %d\n", tempoTotal);

        printf("\nO que deseja fazer?\n");
        printf("1 - Preparar pedido\n");
        printf("2 - Pular pedido (penalidade: -1 tempo)\n");
        printf("Escolha: ");

        int opcao;
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (opcao == 1) {
            if (tempoTotal < atual.tempo) {
                printf("\n❌ Tempo insuficiente! GAME OVER\n");
                break;
            }

            dequeue(&cozinha);
            prepararPedido();
            tempoTotal -= atual.tempo;
            pontuacao += atual.pontos;

            printf("Pedido finalizado! +%d pontos\n", atual.pontos);

        } else if (opcao == 2) {
            dequeue(&cozinha);
            tempoTotal -= 1;

            if (tempoTotal <= 0) {
                printf("\n❌ Tempo esgotado! GAME OVER\n");
                break;
            }

            enqueue(&cozinha, atual);
            printf("Pedido pulado!\n");
            limparTela();
        }
    }

    printf("\nFIM DE JOGO\n");
    printf("Pontuacao final: %d\n", pontuacao);

    system("pause");

    return 0;
}