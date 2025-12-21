#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

// ================= ESTRUTURAS =================

typedef struct {
    int tipo;
    char nome[20];
} Feitico;

typedef struct {
    Feitico itens[MAX];
    int topo;
} Pilha;

typedef struct {
    char nome[30];
    char descricao[100];
    char fraquezas[3][20];
    int vida;
    int vidaMax;
} Boss;

typedef struct {
    int pontos;
    int combo;
    int melhorCombo;
    char ultimaMagia[20];
    int usosConsecutivos;
    int dicasUsadas;
} Jogador;

// ================= FUNCOES DE TELA =================

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ================= PILHA =================

void inicializar(Pilha *p) {
    p->topo = -1;
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

int empilhar(Pilha *p, Feitico f) {
    if (p->topo == MAX - 1) return 0;
    p->itens[++p->topo] = f;
    return 1;
}

int desempilhar(Pilha *p, Feitico *f) {
    if (estaVazia(p)) return 0;
    *f = p->itens[p->topo--];
    return 1;
}

void mostrarPilha(Pilha *p) {
    if (estaVazia(p)) {
        printf("Pilha vazia.\n");
        return;
    }

    printf("\n--- TOPO ---\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%s\n", p->itens[i].nome);
    }
    printf("------------\n");
}

// ================= FEITICOS =================

Feitico criarFeitico(int tipo) {
    Feitico f;
    f.tipo = tipo;

    switch (tipo) {
        case 1: strcpy(f.nome, "Fogo"); break;
        case 2: strcpy(f.nome, "Agua"); break;
        case 3: strcpy(f.nome, "Ar"); break;
        case 4: strcpy(f.nome, "Terra"); break;
        default: strcpy(f.nome, "Desconhecido");
    }
    return f;
}

// ================= MAGIAS (ORDEM NAO IMPORTA) =================

const char* magiaResultado(int t1, int t2) {

    if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
        return "Explosao";

    if ((t1 == 2 && t2 == 1) || (t1 == 1 && t2 == 2))
        return "Vapor";

    if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
        return "Lava";

    if ((t1 == 2 && t2 == 4) || (t1 == 4 && t2 == 2))
        return "Raio";

    if ((t1 == 3 && t2 == 2) || (t1 == 2 && t2 == 3))
        return "Nevoa";

    return "Falha";
}

// ================= SISTEMA DE DICAS =================

void mostrarDica(Boss boss, int nivel, Jogador *jogador) {
    jogador->dicasUsadas++;

    printf("\n--- DICA (Nivel %d) ---\n", nivel);

    switch(nivel) {
        case 1:
            printf("Combine dois feiticos diferentes para criar magias!\n");
            printf("Exemplo: Fogo + Ar = ???\n");
            break;
        case 2:
            printf("Receitas de magia:\n");
            printf("  Fogo + Ar   = Explosao\n");
            printf("  Fogo + Agua = Vapor\n");
            printf("  Fogo + Terra = Lava\n");
            printf("  Agua + Terra = Raio\n");
            printf("  Agua + Ar   = Nevoa\n");
            break;
        case 3:
            printf("%s eh fraco contra: %s\n", boss.nome, boss.fraquezas[0]);
            break;
    }
    printf("----------------------\n");
}

void mostrarTabelaMagias() {
    printf("\n========== TABELA DE COMBINACOES ==========\n");
    printf("|  Feitico 1  |  Feitico 2  |   Magia    |\n");
    printf("|-------------|-------------|------------|\n");
    printf("|    Fogo     |     Ar      |  Explosao  |\n");
    printf("|    Fogo     |    Agua     |   Vapor    |\n");
    printf("|    Fogo     |   Terra     |    Lava    |\n");
    printf("|    Agua     |   Terra     |    Raio    |\n");
    printf("|    Agua     |     Ar      |   Nevoa    |\n");
    printf("============================================\n");
}

// ================= BARRA DE VIDA =================

void mostrarBarraVida(Boss boss) {
    int barraCheia = 20;
    int preenchido = (boss.vida * barraCheia) / boss.vidaMax;

    printf("[");
    for (int i = 0; i < barraCheia; i++) {
        if (i < preenchido)
            printf("#");
        else
            printf("-");
    }
    printf("] %d/%d HP\n", boss.vida, boss.vidaMax);
}

// ================= TUTORIAL =================

void mostrarTutorial() {
    printf("\n");
    printf("========================================\n");
    printf("         BEM-VINDO A BATALHA ARCANA!    \n");
    printf("========================================\n\n");

    printf("OBJETIVO: Derrotar o Boss usando magias!\n\n");

    printf("COMO JOGAR:\n");
    printf("1. EMPILHE feiticos (Fogo, Agua, Ar, Terra)\n");
    printf("2. CONJURE para combinar os 2 do topo\n");
    printf("3. Acerte as FRAQUEZAS do boss!\n\n");

    printf("PILHA - Lembre-se:\n");
    printf("  -> Ultimo a entrar = Primeiro a sair\n");
    printf("  -> Os 2 feiticos do TOPO serao combinados\n\n");

    printf("DICA: Use a opcao 6 para ver as combinacoes!\n");
    printf("========================================\n");

    printf("\nPressione ENTER para comecar...");
    getchar();
}

// ================= BATALHA =================

int calcularDano(Jogador *jogador, int eficaz) {
    int danoBase = eficaz ? 30 : 5;
    int bonus = jogador->combo * 5;
    return danoBase + bonus;
}

int conjurar(Pilha *p, Boss *boss, Jogador *jogador) {
    Feitico f1, f2;

    if (p->topo < 1) {
        printf("Feiticos insuficientes!\n");
        return -1;
    }

    desempilhar(p, &f1);
    desempilhar(p, &f2);

    const char *resultado = magiaResultado(f1.tipo, f2.tipo);

    if (strcmp(resultado, "Falha") == 0) {
        printf("\n>> Combinacao invalida! Feiticos iguais nao funcionam.\n");
        jogador->combo = 0;
        return 0;
    }

    printf("\n*:*:* %s + %s = %s *:*:*\n", f1.nome, f2.nome, resultado);

    // Verificar uso consecutivo da mesma magia
    if (strcmp(resultado, jogador->ultimaMagia) == 0) {
        jogador->usosConsecutivos++;
        if (jogador->usosConsecutivos >= 2) {
            printf("\n>> O boss aprendeu a resistir a %s!\n", resultado);
            printf(">> Dano reduzido! Tente uma magia diferente.\n");
            int danoReduzido = 10;
            boss->vida -= danoReduzido;
            jogador->combo = 0;
            jogador->pontos += 5;
            strcpy(jogador->ultimaMagia, resultado);
            return 0;
        }
    } else {
        jogador->usosConsecutivos = 0;
    }
    strcpy(jogador->ultimaMagia, resultado);

    // Verificar se a magia eh eficaz
    int eficaz = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(resultado, boss->fraquezas[i]) == 0) {
            eficaz = 1;
            break;
        }
    }

    int dano = calcularDano(jogador, eficaz);

    if (eficaz) {
        jogador->combo++;
        if (jogador->combo > jogador->melhorCombo)
            jogador->melhorCombo = jogador->combo;

        jogador->pontos += 100 + (jogador->combo * 25);

        printf("\n>> SUPER EFICAZ contra %s!\n", boss->nome);
        printf(">> Dano: %d", dano);
        if (jogador->combo > 1)
            printf(" (COMBO x%d!)", jogador->combo);
        printf("\n");

        boss->vida -= dano;
    } else {
        jogador->combo = 0;
        jogador->pontos += 10;
        boss->vida -= dano;
        printf("\n>> Acertou, mas nao foi muito eficaz...\n");
        printf(">> Dano: %d\n", dano);
    }

    if (boss->vida < 0) boss->vida = 0;

    return eficaz ? 1 : 0;
}

// ================= MAIN =================

int main() {
    srand(time(NULL));

    Boss bosses[3] = {
        {"Ignivar", "Dragao de Fogo Ancestral",
         {"Vapor", "Raio", "Nevoa"}, 100, 100},

        {"Aeroth", "Tita das Tempestades",
         {"Lava", "Explosao", "Vapor"}, 100, 100},

        {"Terrak", "Colosso da Terra",
         {"Lava", "Raio", "Explosao"}, 100, 100}
    };

    Boss boss = bosses[rand() % 3];

    Pilha pilha;
    inicializar(&pilha);

    Jogador jogador = {0, 0, 0, "", 0, 0};

    int tentativas = 6;
    int opcao, tipo;
    int nivelDica = 1;

    // Tutorial inicial
    limparTela();
    mostrarTutorial();

    while (tentativas > 0 && boss.vida > 0) {
        limparTela();

        printf("============ BATALHA ARCANA ============\n\n");

        printf("BOSS: %s - %s\n", boss.nome, boss.descricao);
        mostrarBarraVida(boss);

        printf("\nTentativas: %d  |  Pontos: %d", tentativas, jogador.pontos);
        if (jogador.combo > 0)
            printf("  |  Combo: x%d", jogador.combo);
        printf("\n");

        printf("\n-------- ACOES --------\n");
        printf("1 - Empilhar feitico\n");
        printf("2 - CONJURAR MAGIA!\n");
        printf("3 - Ver pilha\n");
        printf("4 - Limpar pilha\n");
        printf("5 - Pedir dica\n");
        printf("6 - Tabela de magias\n");
        printf("-----------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nEscolha o feitico:\n");
                printf("  [1] Fogo   [2] Agua\n");
                printf("  [3] Ar     [4] Terra\n");
                printf("Feitico: ");
                scanf("%d", &tipo);
                if (tipo >= 1 && tipo <= 4) {
                    Feitico f = criarFeitico(tipo);
                    if (empilhar(&pilha, f))
                        printf("\n>> %s adicionado a pilha!\n", f.nome);
                    else
                        printf("\n>> Pilha cheia!\n");
                } else {
                    printf("\n>> Feitico invalido!\n");
                }
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            case 2:
                conjurar(&pilha, &boss, &jogador);
                tentativas--;
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            case 3:
                mostrarPilha(&pilha);
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            case 4:
                inicializar(&pilha);
                printf("\n>> Pilha limpa!\n");
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            case 5:
                mostrarDica(boss, nivelDica, &jogador);
                if (nivelDica < 3) nivelDica++;
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            case 6:
                mostrarTabelaMagias();
                printf("\nPressione ENTER...");
                getchar(); getchar();
                break;

            default:
                printf("\n>> Opcao invalida!\n");
                printf("\nPressione ENTER...");
                getchar(); getchar();
        }
    }

    // Tela final
    limparTela();
    printf("========================================\n");

    if (boss.vida <= 0) {
        printf("        *** VITORIA! ***\n");
        printf("========================================\n\n");
        printf("Voce derrotou %s!\n\n", boss.nome);

        int bonus = tentativas * 50;
        int penalidade = jogador.dicasUsadas * 20;
        int pontosFinal = jogador.pontos + bonus - penalidade;

        printf("--- PONTUACAO FINAL ---\n");
        printf("Pontos base:       %d\n", jogador.pontos);
        printf("Bonus tentativas:  +%d\n", bonus);
        if (jogador.dicasUsadas > 0)
            printf("Penalidade dicas:  -%d\n", penalidade);
        printf("-----------------------\n");
        printf("TOTAL:             %d\n", pontosFinal);
        printf("\nMelhor combo: x%d\n", jogador.melhorCombo);

        if (pontosFinal >= 400)
            printf("\nRank: S - MESTRE ARCANO!\n");
        else if (pontosFinal >= 300)
            printf("\nRank: A - Excelente!\n");
        else if (pontosFinal >= 200)
            printf("\nRank: B - Muito bom!\n");
        else
            printf("\nRank: C - Continue praticando!\n");

    } else {
        printf("        DERROTA...\n");
        printf("========================================\n\n");
        printf("%s venceu desta vez.\n", boss.nome);
        printf("Pontos obtidos: %d\n", jogador.pontos);
        printf("\nDica: Tente variar suas magias e\n");
        printf("acerte as fraquezas do boss!\n");
    }

    printf("\n========================================\n");

    return 0;
}
