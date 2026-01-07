# 🏰 Jogo da Torre Abandonada – Documentação

## 1. Introdução

Este trabalho tem como objetivo demonstrar, de forma prática e didática, o uso da estrutura de dados Árvore Binária na linguagem C, por meio do desenvolvimento de um jogo de exploração de calabouço em modo CLI (Command Line Interface).

No jogo, o jogador navega por uma torre misteriosa onde cada sala representa um nó da árvore binária, e as escolhas de caminho (esquerda ou direita) determinam a navegação pelos filhos de cada nó.

---

## 2. Objetivo do Jogo

O jogador assume o papel de um aventureiro que deve:

* Explorar os andares da torre abandonada
* Escolher entre dois caminhos a cada sala (esquerda ou direita)
* Enfrentar inimigos, encontrar tesouros e comerciar com mercadores
* Sobreviver o máximo de andares possível

O jogo termina quando:

* A vida do jogador chega a zero (derrota)

O objetivo é alcançar o maior número de andares possível antes de sucumbir aos perigos da torre.

---

## 3. Conceito da Estrutura de Árvore Binária

A árvore binária é uma estrutura de dados hierárquica onde:

* Cada nó possui no máximo dois filhos (esquerdo e direito)
* A navegação ocorre sempre do nó pai para um dos filhos
* A estrutura cresce dinamicamente conforme o jogador avança

No contexto do jogo:

* Cada sala é um nó da árvore
* A sala inicial é a raiz da árvore
* Escolher esquerda navega para o filho esquerdo
* Escolher direita navega para o filho direito
* Novas salas são criadas sob demanda (alocação dinâmica)

Essa escolha representa fielmente o funcionamento de uma árvore binária na computação.

---

## 4. Estruturas de Dados Utilizadas

### 4.1 Estrutura Sala

```c
typedef struct Sala {
    int tipo;
    struct Sala *esq;
    struct Sala *dir;
} Sala;
```

Representa um nó da árvore (uma sala da torre):

* tipo: tipo da sala (0=vazia, 1=inimigo, 2=tesouro, 3=venda, 4=misteriosa)
* esq: ponteiro para o filho esquerdo (passagem sombria)
* dir: ponteiro para o filho direito (escadaria instável)

---

### 4.2 Estrutura Jogador

```c
typedef struct {
    int vida;
    int moedas;
    int profundidade;
} Jogador;
```

Armazena o estado atual do jogador:

* vida: pontos de vida restantes (inicia com 20)
* moedas: quantidade de moedas coletadas (inicia com 10)
* profundidade: andar atual da torre (inicia em 1)

---

### 4.3 Tipos de Salas

O jogo possui 5 tipos de salas com diferentes probabilidades de aparição:

| Tipo | Nome | Descrição | Probabilidade Base |
|------|------|-----------|-------------------|
| 0 | Vazia | Sala silenciosa sem eventos | 15% |
| 1 | Inimigo | Criatura que causa dano | 40% (aumenta com profundidade) |
| 2 | Tesouro | Baú com moedas | 15% |
| 3 | Venda | Mercador para comprar vida | 15% (rara) |
| 4 | Misteriosa | Evento aleatório (bom ou ruim) | 15% |

---

## 5. Funções Principais

### 5.1 Funções da Árvore

#### criarSala

```c
Sala* criarSala(int tipo);
```

Aloca dinamicamente uma nova sala (nó) com o tipo especificado. Inicializa os ponteiros esquerdo e direito como NULL.

---

#### avancarSala

```c
Sala* avancarSala(Sala *atual, int escolha, Jogador *j);
```

Navega para o filho esquerdo ou direito da sala atual. Se o filho não existir, cria uma nova sala com tipo aleatório baseado na profundidade.

---

#### liberarTorre

```c
void liberarTorre(Sala *s);
```

Libera recursivamente toda a memória alocada para a árvore, percorrendo em pós-ordem (esquerda, direita, raiz).

---

### 5.2 Funções de Geração

#### gerarSalaAleatoria

```c
int gerarSalaAleatoria(int profundidade);
```

Gera um tipo de sala baseado em probabilidades. A chance de encontrar inimigos aumenta conforme a profundidade:

* Probabilidade de inimigo: 40% + (profundidade × 2%)

---

### 5.3 Funções de Gameplay

#### processarSala

```c
void processarSala(Sala *s, Jogador *j);
```

Executa o evento correspondente ao tipo da sala:

| Tipo | Evento |
|------|--------|
| Vazia | Nenhum efeito |
| Inimigo | Dano de 3-8 + profundidade |
| Tesouro | Ganho de 4-11 moedas |
| Venda | Abre menu de compra |
| Misteriosa | 50% chance de dano (2-7) ou ganho (3-7 moedas) |

---

#### salaVenda

```c
void salaVenda(Jogador *j);
```

Permite ao jogador comprar pontos de vida:

* Custo: 6 moedas por ponto de vida
* Verifica se o jogador possui moedas suficientes

---

### 5.4 Funções de Interface

#### limparTela

```c
void limparTela();
```

Limpa a tela do terminal. Compatível com Windows (`cls`) e Linux/Mac (`clear`).

---

#### mostrarStatus

```c
void mostrarStatus(Jogador j);
```

Exibe o status atual do jogador: vida, moedas e andar atual.

---

## 6. Lógica do Jogo

### 6.1 Regras

* O jogador inicia com **20 de vida** e **10 moedas**
* A cada andar, deve escolher entre **esquerda** ou **direita**
* Escolhas inválidas causam **1 de dano**
* A dificuldade aumenta com a profundidade (mais inimigos, mais dano)
* O jogo continua até a vida chegar a zero

### 6.2 Fluxo do Jogo

O jogo funciona em um laço principal:

1. Limpa a tela e exibe o status do jogador
2. Processa os eventos da sala atual
3. Verifica se o jogador ainda está vivo
4. Apresenta as opções de caminho:

| Opção | Ação |
|-------|------|
| 1 | Passagem sombria à esquerda |
| 2 | Escadaria instável à direita |

5. Incrementa a profundidade e avança para a próxima sala
6. Repete até a morte do jogador

### 6.3 Sistema de Dificuldade Progressiva

* **Probabilidade de inimigos**: Aumenta 2% por andar
* **Dano dos inimigos**: Base (3-8) + profundidade atual
* **Recompensas**: Permanecem constantes

---

## 7. Representação Visual da Árvore

```
                    [Raiz]
                   /      \
              [Esq]        [Dir]
             /    \       /    \
          [...]  [...]  [...]  [...]
```

Cada nó representa uma sala, e a navegação ocorre sempre descendo na árvore.

---

## 8. Conclusão

Este projeto demonstra de forma clara e prática:

* O uso da estrutura de dados Árvore Binária
* Alocação dinâmica de memória em C
* Navegação recursiva em estruturas hierárquicas
* Liberação correta de memória (evitando memory leaks)
* Organização de código em C com estruturas e funções

O jogo apresenta um equilíbrio entre simplicidade e complexidade, sendo adequado para fins educacionais e avaliação acadêmica.

---

## 9. Compilação e Execução do Programa

O projeto é disponibilizado de duas formas, facilitando o uso tanto para usuários finais quanto para avaliadores que desejem compilar o código-fonte.

---

### 9.1 Execução via Arquivo Executável

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

### 9.2 Compilação Manual do Código-Fonte

Também é fornecido o código-fonte (`arvore.c`), possibilitando a compilação manual do programa.

#### Requisitos:

* Compilador **GCC** instalado (disponível para Windows, Linux e Mac)

#### Comando de compilação:

```bash
gcc arvore.c -o main
```

---

**Autores:** Pedro Henrique Castro, Ruan Ripardo, Samuel Pinheiro

Trabalho acadêmico – Estrutura de Dados em C
