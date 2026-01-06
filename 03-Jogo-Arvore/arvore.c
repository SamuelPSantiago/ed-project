#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define VAZIA      0
#define INIMIGO    1
#define TESOURO    2
#define ARMADILHA  3
#define LOJA       4


typedef struct Sala {
    int tipo;
    int perigo;
    struct Sala *esq;
    struct Sala *dir;
    struct Sala *extra;
} Sala;


Sala* gerarSala();
void descreverSala(Sala *sala);
void explorar(Sala *atual, int *vida, int *ouro);
void loja(int *vida, int *ouro);
void mostrarCaminhos(int temExtra);
void limparTela();

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

Sala* gerarSala() {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    int chance = rand() % 100;

    if (chance < 30) nova->tipo = VAZIA;
    else if (chance < 60) nova->tipo = INIMIGO;
    else if (chance < 80) nova->tipo = TESOURO;
    else if (chance < 90) nova->tipo = ARMADILHA;
    else nova->tipo = LOJA;

    nova->perigo = rand() % 10 + 1;
    nova->esq = nova->dir = nova->extra = NULL;
    return nova;
}

void descreverSala(Sala *sala) {
    switch (sala->tipo) {
        case VAZIA:
            printf("A sala está vazia. O silêncio é desconfortável.\n");
            break;
        case INIMIGO:
            printf("Um inimigo aparece! Ele claramente odeia esse emprego.\n");
            break;
        case TESOURO:
            printf("Você encontra um tesouro esquecido. Finalmente algo bom.\n");
            break;
        case ARMADILHA:
            printf("Uma armadilha ativa! Péssimo dia pra andar distraído.\n");
            break;
        case LOJA:
            printf("Uma lojinha improvisada surge. Capitalismo nunca dorme.\n");
            break;
    }
}

void loja(int *vida, int *ouro) {
    int escolha;
    printf("\nLOJA\n");
    printf("❤️ Vida: %d | 💰 Ouro: %d\n", *vida, *ouro);
    printf("1 - Comprar +20 de vida (30 moedas)\n");
    printf("2 - Ir embora desconfiado\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    if (escolha == 1 && *ouro >= 30) {
        *ouro -= 30;
        *vida += 20;
        printf("A poção funciona. O gosto não.\n");
    } else if (escolha == 1) {
        printf("O vendedor te olha com desprezo.\n");
    }
}

void mostrarCaminhos(int temExtra) {
    const char *esq[] = {
        "Porta rangendo à esquerda",
        "Corredor escuro à esquerda",
        "Escada quebrada à esquerda",
        "Passagem estreita à esquerda",
        "Caminho coberto de poeira à esquerda"
    };

    const char *dir[] = {
        "Escadaria em espiral à direita",
        "Porta de pedra à direita",
        "Corredor largo à direita",
        "Passagem descendente à direita",
        "Caminho iluminado à direita"
    };

    const char *extra[] = {
        "Passagem secreta atrás da parede",
        "Alçapão suspeito no chão",
        "Fenda mal escondida na parede"
    };

    printf("\nCaminhos disponíveis:");
    printf("\n1 - %s", esq[rand() % 5]);
    printf("\n2 - %s", dir[rand() % 5]);

    if (temExtra)
        printf("\n3 - %s", extra[rand() % 3]);
}

void explorar(Sala *atual, int *vida, int *ouro) {
    int escolha;

    while (*vida > 0) {
        printf("\n---------------------------------\n");
        descreverSala(atual);

        if (atual->tipo == INIMIGO) {
            int dano = atual->perigo;
            *vida -= dano;
            printf("Você perde %d de vida.\n", dano);
        }
        else if (atual->tipo == TESOURO) {
            int ganho = rand() % 20 + 10;
            *ouro += ganho;
            printf("Você ganha %d moedas.\n", ganho);
        }
        else if (atual->tipo == ARMADILHA) {
            int dano = atual->perigo * 2;
            *vida -= dano;
            printf("A armadilha causa %d de dano!\n", dano);
        }
        else if (atual->tipo == LOJA) {
            loja(vida, ouro);
        }

        printf("❤️ Vida: %d | 💰 Ouro: %d\n", *vida, *ouro);

        if (*vida <= 0) {
            printf("\n💀 Você morreu. A torre segue indiferente.\n");
            return;
        }

        if (!atual->esq) atual->esq = gerarSala();
        if (!atual->dir) atual->dir = gerarSala();
        if (!atual->extra && rand() % 100 < 25)
            atual->extra = gerarSala();

        mostrarCaminhos(atual->extra != NULL);

        printf("\nEscolha: ");
        scanf("%d", &escolha);

        limparTela();  
        
        if (escolha == 1) atual = atual->esq;
        else if (escolha == 2) atual = atual->dir;
        else if (escolha == 3 && atual->extra) atual = atual->extra;
    }
}

int main() {
    srand(time(NULL));

    int vida = 100, ouro = 50;
    Sala *inicio = gerarSala();

    limparTela();
    printf("🏰 A TORRE ABANDONADA — EXPLORAÇÃO INFINITA\n");
    printf("Entrar foi sua escolha.\n");

    explorar(inicio, &vida, &ouro);
    return 0;
}
