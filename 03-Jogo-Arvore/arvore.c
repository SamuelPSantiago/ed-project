#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct Sala {
    int tipo;               // 0=vazia, 1=inimigo, 2=tesouro, 3=venda, 4=misteriosa
    struct Sala *esq;
    struct Sala *dir;
} Sala;

typedef struct {
    int vida;
    int moedas;
    int profundidade;
} Jogador;


void limparTela() {
    system(CLEAR);
}

Sala* criarSala(int tipo) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    nova->tipo = tipo;
    nova->esq = NULL;
    nova->dir = NULL;
    return nova;
}

int gerarSalaAleatoria(int profundidade) {
    int r = rand() % 100;

    if (r < 40 + profundidade * 2) return 1; // inimigo
    if (r < 55) return 0;                     // vazia
    if (r < 70) return 2;                     // tesouro
    if (r < 85) return 4;                     // misteriosa
    return 3;                                 // venda (rara)
}

void mostrarStatus(Jogador j) {
    printf("❤️ Vida: %d | 💰 Moedas: %d | 🏰 Andar: %d\n",
           j.vida, j.moedas, j.profundidade);
}

void salaVenda(Jogador *j) {
    int qtd;
    printf("\nMercador sombrio aparece...\n");
    printf("💊 Vida custa 6 moedas por ponto\n");
    printf("Quantos pontos deseja comprar? ");
    scanf("%d", &qtd);

    int custo = qtd * 6;

    if (custo <= j->moedas && qtd > 0) {
        j->moedas -= custo;
        j->vida += qtd;
        printf("✅ Compra realizada!\n");
    } else {
        printf("❌ O mercador ri da sua pobreza.\n");
    }
}

void processarSala(Sala *s, Jogador *j) {
    int dano, ganho;

    switch (s->tipo) {

        case 0:
            printf("\n😶 Sala vazia... estranhamente silenciosa.\n");
            break;

        case 1:
            dano = (rand() % 6) + 3 + j->profundidade;
            j->vida -= dano;
            printf("\n👹 Inimigo surge das sombras!\n");
            printf("💥 Você perde %d de vida!\n", dano);
            break;

        case 2:
            ganho = (rand() % 8) + 4;
            j->moedas += ganho;
            printf("\n💰 Você encontra um baú!\n");
            printf("✨ Ganhou %d moedas!\n", ganho);
            break;

        case 3:
            salaVenda(j);
            break;

        case 4: {
            int evento = rand() % 2;
            if (evento == 0) {
                dano = (rand() % 6) + 2;
                j->vida -= dano;
                printf("\n❓ Uma armadilha escondida!\n");
                printf("💀 Você perde %d de vida!\n", dano);
            } else {
                ganho = (rand() % 5) + 3;
                j->moedas += ganho;
                printf("\n✨ Um espírito antigo te ajuda!\n");
                printf("💰 Ganhou %d moedas!\n", ganho);
            }
            break;
        }
    }
}

Sala* avancarSala(Sala *atual, int escolha, Jogador *j) {
    if (escolha == 1) {
        if (!atual->esq)
            atual->esq = criarSala(gerarSalaAleatoria(j->profundidade));
        return atual->esq;
    } else {
        if (!atual->dir)
            atual->dir = criarSala(gerarSalaAleatoria(j->profundidade));
        return atual->dir;
    }
}

void liberarTorre(Sala *s) {
    if (!s) return;
    liberarTorre(s->esq);
    liberarTorre(s->dir);
    free(s);
}

// ---------- FUNÇÃO PRINCIPAL ----------

int main() {
    srand(time(NULL));

    Jogador jogador = {20, 10, 1};
    Sala *raiz = criarSala(0);
    Sala *atual = raiz;

    int escolha;

    while (jogador.vida > 0) {
        limparTela();
        mostrarStatus(jogador);
        processarSala(atual, &jogador);

        if (jogador.vida <= 0) break;

        printf("\nEscolha seu caminho:\n");
        printf("1 - Passagem sombria à esquerda\n");
        printf("2 - Escadaria instável à direita\n");
        printf("\n-> Escolha: ");
        scanf("%d", &escolha);

        if (escolha != 1 && escolha != 2) {
            printf("\n❌ Você tropeça na indecisão e perde 1 de vida.\n");
            jogador.vida--;
            getchar();
            getchar();
            continue;
        }

        jogador.profundidade++;
        atual = avancarSala(atual, escolha, &jogador);
    }

    limparTela();
    printf("\n💀 Você tombou na Torre Abandonada...\n");
    printf("🏰 Andar alcançado: %d\n", jogador.profundidade);
    printf("💰 Moedas finais: %d\n", jogador.moedas);

    liberarTorre(raiz);
    return 0;
}
