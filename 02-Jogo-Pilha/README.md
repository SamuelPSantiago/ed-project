# 🔮 Jogo das Magias – Documentação

## 1. Introdução

Este trabalho tem como objetivo demonstrar, de forma prática e didática, o uso da estrutura de dados Pilha (Stack) na linguagem C, por meio do desenvolvimento de um jogo interativo de combate mágico em modo CLI (Command Line Interface).

No jogo, elementos mágicos são armazenados em uma pilha e combinados para formar magias, seguindo a lógica LIFO (Last In, First Out), simulando um sistema de conjuração onde os últimos elementos inseridos são os primeiros a serem utilizados.

---

## 2. Objetivo do Jogo

O jogador assume o papel de um mago que deve:

* Empilhar elementos mágicos
* Combinar elementos para conjurar magias
* Utilizar as magias corretas contra o inimigo
* Administrar corretamente o número de tentativas disponíveis

O jogo termina quando:

* O boss é derrotado após conjurar as magias corretas (vitória)
* As tentativas acabam antes da derrota do boss (derrota)

---

## 3. Conceito da Estrutura de Pilha

A pilha é uma estrutura de dados linear que segue o princípio:

LIFO – Last In, First Out
O último elemento a entrar é o primeiro a sair.

No contexto do jogo:

* Cada elemento mágico é um item empilhado
* Novos elementos são inseridos no topo da pilha (push)
* A conjuração utiliza sempre os elementos do topo (pop)

Essa escolha representa fielmente o funcionamento de uma pilha na computação.

---

## 4. Estruturas de Dados Utilizadas

### 4.1 Estrutura Feitico

```c
typedef struct {
    int tipo;
    char nome[20];
} Feitico;
```

Representa um elemento mágico:

* tipo: identificador numérico do elemento (1=Fogo, 2=Água, 3=Ar, 4=Terra)
* nome: nome do elemento para exibição

---

### 4.2 Estrutura Pilha

```c
#define MAX 10

typedef struct {
    Feitico itens[MAX];
    int topo;
} Pilha;
```

A pilha é implementada usando um vetor estático de feitiços:

* itens: armazena os feitiços empilhados
* topo: indica a posição do último feitiço inserido

---

### 4.3 Estrutura Boss

```c
typedef struct {
    char nome[30];
    char descricao[100];
    char fraquezas[3][20];
} Boss;
```

Representa o inimigo a ser derrotado:

* nome: identificação do boss
* descricao: descrição temática do inimigo
* fraquezas: três magias às quais o boss é vulnerável

O jogo possui 3 bosses que são selecionados aleatoriamente:

| Boss | Descrição | Fraquezas |
|------|-----------|-----------|
| Ignivar | Dragão de Fogo Ancestral | Vapor, Raio, Névoa |
| Aeroth | Titã das Tempestades | Lava, Explosão, Vapor |
| Terrak | Colosso da Terra | Lava, Raio, Explosão |

---

## 5. Funções Principais

### 5.1 Funções da Pilha

#### inicializar

```c
void inicializar(Pilha *p);
```

Inicializa a pilha, definindo topo como -1.

---

#### estaVazia

```c
int estaVazia(Pilha *p);
```

Verifica se a pilha está vazia. Retorna 1 se vazia, 0 caso contrário.

---

#### empilhar

```c
int empilhar(Pilha *p, Feitico f);
```

Insere um novo feitiço no topo da pilha. Retorna 1 em sucesso, 0 se a pilha estiver cheia.

---

#### desempilhar

```c
int desempilhar(Pilha *p, Feitico *f);
```

Remove o feitiço do topo da pilha e o armazena no ponteiro fornecido. Retorna 1 em sucesso, 0 se a pilha estiver vazia.

---

#### mostrarPilha

```c
void mostrarPilha(Pilha *p);
```

Exibe todos os feitiços da pilha, do topo para a base.

---

### 5.2 Funções de Feitiços

#### criarFeitico

```c
Feitico criarFeitico(int tipo);
```

Cria um feitiço baseado no tipo informado:

| Tipo | Nome |
|------|------|
| 1 | Fogo |
| 2 | Água |
| 3 | Ar |
| 4 | Terra |

---

### 5.3 Funções de Magia

#### magiaResultado

```c
const char* magiaResultado(int t1, int t2);
```

Combina dois tipos de feitiços e retorna o nome da magia resultante. A ordem dos elementos não interfere na conjuração.

| Combinação | Magia Resultante |
|------------|------------------|
| Fogo + Ar | Explosão |
| Fogo + Água | Vapor |
| Fogo + Terra | Lava |
| Água + Terra | Raio |
| Água + Ar | Névoa |
| Outras | Falha |

---

#### conjurar

```c
int conjurar(Pilha *p, Boss boss, int *acertos);
```

Utiliza os dois feitiços do topo da pilha para formar uma magia e verifica se é eficaz contra o boss. Retorna 1 se a magia foi eficaz, 0 caso contrário.

---

### 5.4 Funções de Interface

#### limparTela

```c
void limparTela();
```

Limpa a tela do terminal. Compatível com Windows (`cls`) e Linux/Mac (`clear`).

---

#### mostrarTutorial

```c
void mostrarTutorial();
```

Exibe as instruções do jogo ao iniciar, explicando o objetivo, mecânicas e dicas.

---

#### mostrarTabelaMagias

```c
void mostrarTabelaMagias();
```

Exibe uma tabela com todas as combinações possíveis de feitiços e suas magias resultantes.

---

## 6. Lógica do Jogo

### 6.1 Regras

* O jogador possui **4 tentativas** para derrotar o boss
* São necessárias **3 magias eficazes** para vencer
* Cada conjuração consome uma tentativa e dois feitiços da pilha
* A ordem dos feitiços não importa na combinação
* O boss é escolhido aleatoriamente no início do jogo

### 6.2 Fluxo do Jogo

O jogo funciona em um laço principal:

1. Exibe um tutorial explicativo ao iniciar
2. Limpa a tela e exibe informações do boss e progresso
3. O jogador escolhe uma opção do menu:

| Opção | Ação |
|-------|------|
| 1 | Empilhar feitiço |
| 2 | Conjurar magia |
| 3 | Ver pilha |
| 4 | Limpar pilha |
| 5 | Mostrar tabela de combinações |
| 0 | Sair |

4. O sistema verifica se a magia é eficaz contra o boss
5. Atualiza o número de tentativas e acertos
6. Verifica condição de vitória (3 acertos) ou derrota (0 tentativas)

---

## 7. Conclusão

Este projeto demonstra de forma clara e prática:

* O uso da estrutura de dados Pilha
* Aplicação do conceito LIFO em um problema real
* Organização de código em C
* Uso de estruturas, funções e controle de fluxo

O jogo apresenta um equilíbrio entre simplicidade e complexidade, sendo adequado para fins educacionais e avaliação acadêmica.

---

## 8. Compilação e Execução do Programa

O projeto é disponibilizado de duas formas, facilitando o uso tanto para usuários finais quanto para avaliadores que desejem compilar o código-fonte.

---

### 8.1 Execução via Arquivo Executável

Para facilitar a utilização, o trabalho acompanha um **arquivo executável já compilado**.

Basta executar o arquivo correspondente ao sistema operacional:

* Em sistemas Windows:

```bash
main.exe
```

* Em sistemas Linux/Mac:

```bash
./main
```

Essa opção permite rodar o jogo imediatamente, sem necessidade de compilação prévia.

---

### 8.2 Compilação Manual do Código-Fonte

Também é fornecido o código-fonte (`pilha.c`), possibilitando a compilação manual do programa.

#### Requisitos:

* Compilador **GCC** instalado (disponível para Windows, Linux e Mac)

#### Comando de compilação:

```bash
gcc pilha.c -o main
```

Após a compilação, o programa pode ser executado com:

* Windows:
```bash
main.exe
```

* Linux/Mac:
```bash
./main
```

---

**Autores:** Pedro Henrique Castro, Ruan Ripardo, Samuel Pinheiro 

Trabalho acadêmico – Estrutura de Dados em C