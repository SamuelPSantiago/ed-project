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
} Boss;

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

// ================= BATALHA =================

int conjurar(Pilha *p, Boss boss, int *acertos) {
    Feitico f1, f2;

    if (p->topo < 1) {
        printf("Feiticos insuficientes!\n");
        return 0;
    }

    desempilhar(p, &f1);
    desempilhar(p, &f2);

    const char *resultado = magiaResultado(f1.tipo, f2.tipo);

    printf("\nMagia conjurada: %s\n", resultado);

    for (int i = 0; i < 3; i++) {
        if (strcmp(resultado, boss.fraquezas[i]) == 0) {
            printf(">> Foi eficaz contra %s!\n", boss.nome);
            (*acertos)++;
            return 1;
        }
    }

    printf(">> Nao teve efeito...\n");
    return 0;
}

// ================= SISTEMA DE DICAS =================

void mostrarTutorial() {
    printf("\n");
    printf("================================================\n");
    printf("|          BEM-VINDO A BATALHA ARCANA          |\n");
    printf("================================================\n");
    printf("|                                              |\n");
    printf("| OBJETIVO: Derrotar o Boss usando magias!     |\n");
    printf("|                                              |\n");
    printf("| COMO JOGAR:                                  |\n");
    printf("| 1. EMPILHE feiticos (Fogo, Agua, Ar, Terra)  |\n");
    printf("| 2. CONJURE para combinar os 2 do topo        |\n");
    printf("| 3. Acerte as FRAQUEZAS do boss!              |\n");
    printf("|                                              |\n");
    printf("| PILHA - Lembre-se:                           |\n");
    printf("|   -> Ultimo a entrar = Primeiro a sair       |\n");
    printf("|   -> Os 2 feiticos do TOPO serao combinados  |\n");
    printf("|                                              |\n");
    printf("| DICA: Use a opcao 5 para ver as combinacoes! |\n");
    printf("================================================\n");
    printf("Pressione ENTER para comecar...");
    getchar();
}

void mostrarTabelaMagias() {
    printf("\n========== TABELA DE COMBINACOES ==========\n");
    printf("|  Feitico 1  |  Feitico 2  |    Magia    |\n");
    printf("|-------------|-------------|-------------|\n");
    printf("|    Fogo     |      Ar     |   Explosao  |\n");
    printf("|    Fogo     |     Agua    |    Vapor    |\n");
    printf("|    Fogo     |    Terra    |     Lava    |\n");
    printf("|    Agua     |    Terra    |     Raio    |\n");
    printf("|    Agua     |      Ar     |    Nevoa    |\n");
    printf("===========================================\n");
}

// ================= MAIN =================

int main() {
    srand(time(NULL));

    Boss bosses[3] = {
        {"Ignivar", "Dragao de Fogo Ancestral",
         {"Vapor", "Raio", "Nevoa"}},

        {"Aeroth", "Tita das Tempestades",
         {"Lava", "Explosao", "Vapor"}},

        {"Terrak", "Colosso da Terra",
         {"Lava", "Raio", "Explosao"}}
    };

    Boss boss = bosses[rand() % 3];

    Pilha pilha;
    inicializar(&pilha);

    int tentativas = 4;
    int acertos = 0;
    int opcao, tipo;

    limparTela();
    mostrarTutorial();

    while (tentativas > 0 && acertos < 3) {
        limparTela();

        printf("============== BATALHA ARCANA ==============\n");
        printf("| Boss: %-34s |\n", boss.nome);
        printf("| Descricao: %-29s |\n", boss.descricao);
        printf("| Tentativas restantes: %-18d |\n", tentativas);
        printf("| Progresso: %-1d / 3 magias eficazes         |\n", acertos);
        printf("============================================\n");
        printf("| 1 | Empilhar feitico                     |\n");
        printf("| 2 | Conjurar magia                       |\n");
        printf("| 3 | Ver pilha                            |\n");
        printf("| 4 | Limpar pilha                         |\n");
        printf("| 5 | Mostrar feiticos                     |\n");
        printf("| 0 | Sair                                 |\n");
        printf("============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nEscolha o feitico:\n");
                printf("  [1] Fogo   [2] Agua\n");
                printf("  [3] Ar     [4] Terra\n");
                printf("Feitico: ");
                scanf("%d", &tipo);
                empilhar(&pilha, criarFeitico(tipo));
                break;

            case 2:
                conjurar(&pilha, boss, &acertos);
                tentativas--;
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;

            case 3:
                mostrarPilha(&pilha);
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;

            case 4:
                inicializar(&pilha);
                printf("Pilha limpa!\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;

            case 5:
                mostrarTabelaMagias();
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
                break;

            case 0:
                return 0;
                break;

            default:
                printf("Opcao invalida!\n");
                printf("\nPressione ENTER para continuar...");
                getchar(); getchar();
        }
    }

    limparTela();

    if (acertos >= 3)
        printf("VITORIA! O boss foi derrotado!\n");
    else
        printf("DERROTA... O boss venceu.\n");

    return 0;
}
