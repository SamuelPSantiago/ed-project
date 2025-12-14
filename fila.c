#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ---------- ESTRUTURA DO PEDIDO ----------
typedef struct {
    char nome[20];
    int tempo;
    int pontos;
} Pedido;

// ---------- FILA ----------
typedef struct {
    Pedido fila[50];
    int inicio;
    int fim;
} Fila;

// ---------- FUNÇÕES DA FILA ----------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila *f) {
    return f->inicio == f->fim;
}

void enqueue(Fila *f, Pedido p) {
    f->fila[f->fim] = p;
    f->fim++;
}

Pedido dequeue(Fila *f) {
    Pedido p = f->fila[f->inicio];
    f->inicio++;
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

// ---------- TELA DE LOAD ----------
void prepararPedido() {
    printf("Preparando");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

// ---------- MOSTRAR FILA ----------
void mostrarFila(Fila *f) {
    printf("\nPedidos na fila:\n");
    for (int i = f->inicio; i < f->fim; i++) {
        printf("- %s (tempo %d | pontos %d)\n",
               f->fila[i].nome,
               f->fila[i].tempo,
               f->fila[i].pontos);
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

    // Gerar pedidos iniciais
    for (int i = 0; i < numPedidos; i++) {
        Pedido p = gerarPedido();
        enqueue(&cozinha, p);
        tempoTotal += 2;
    }

    // Loop principal
    while (!filaVazia(&cozinha)) {
        system("cls || clear");
        
        printf("=== JOGO DA COZINHA ===\n");
        
        mostrarFila(&cozinha);

        Pedido atual = dequeue(&cozinha);

        printf("\nPedido atual: %s\n", atual.nome);
        printf("Tempo: %d | Pontos: %d\n", atual.tempo, atual.pontos);
        printf("Tempo restante: %d\n", tempoTotal);

        printf("\nO que deseja fazer?\n");
        printf("1 - Preparar pedido\n");
        printf("2 - Pular pedido (penalidade: -1 tempo)\n");
        printf("Escolha: ");

        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            system("cls || clear");
            
            if (tempoTotal < atual.tempo) {
                printf("\n❌ Tempo insuficiente! GAME OVER\n");
                break;
            }

            prepararPedido();
            tempoTotal -= atual.tempo;
            pontuacao += atual.pontos;

            printf("Pedido finalizado! +%d pontos\n", atual.pontos);
        } else {
            printf("Pedido pulado!\n");
            tempoTotal -= 1;
            enqueue(&cozinha, atual);
        }

        if (tempoTotal <= 0) {
            printf("\n❌ Tempo esgotado! GAME OVER\n");
            break;
        }
    }

    printf("\n🏁 FIM DE JOGO\n");
    printf("Pontuacao final: %d\n", pontuacao);

    return 0;
}