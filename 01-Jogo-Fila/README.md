# 🍳 Jogo da Cozinha – Documentação

## 1. Introdução

Este trabalho tem como objetivo demonstrar, de forma prática e didática, o uso da **estrutura de dados Fila (Queue)** na linguagem **C**, por meio do desenvolvimento de um jogo simples de gerenciamento de cozinha.

No jogo, pedidos de comida são organizados em uma fila e processados de acordo com a lógica **FIFO (First In, First Out)**, simulando o funcionamento real de uma cozinha.

---

## 2. Objetivo do Jogo

O jogador assume o papel de um cozinheiro que deve:

* Gerenciar pedidos que chegam à cozinha
* Decidir quais pedidos preparar ou adiar
* Administrar o tempo disponível
* Acumular a maior pontuação possível

O jogo termina quando:

* Todos os pedidos são preparados (vitória)
* O tempo acaba antes da finalização (derrota)

---

## 3. Conceito da Estrutura de Fila

A **fila** é uma estrutura de dados linear que segue o princípio:

 **FIFO – First In, First Out**
 O primeiro elemento a entrar é o primeiro a sair.

No contexto do jogo:

* Cada **pedido** é um elemento da fila
* Novos pedidos entram no **final da fila** (`enqueue`)
* O pedido a ser tratado é sempre o **primeiro da fila** (`dequeue`)

Essa escolha representa fielmente o funcionamento de pedidos em uma cozinha real.

---

## 4. Estruturas de Dados Utilizadas

### 4.1 Estrutura Pedido

```c
typedef struct {
    char nome[20];
    int tempo;
    int pontos;
} Pedido;
```

Cada pedido possui:

* `nome`: nome da comida
* `tempo`: tempo necessário para preparo
* `pontos`: pontuação obtida ao concluir o pedido

---

### 4.2 Estrutura Fila

```c
typedef struct {
    Pedido fila[50];
    int inicio;
    int fim;
} Fila;
```

A fila é implementada usando um **vetor estático**, controlado por dois índices:

* `inicio`: posição do primeiro elemento
* `fim`: posição onde o próximo elemento será inserido

---

## 5. Funções Principais

### 5.1 Inicialização da Fila

```c
void inicializarFila(Fila *f);
```

Inicializa a fila, definindo `inicio` e `fim` como zero.

---

### 5.2 Inserção na Fila (enqueue)

```c
void enqueue(Fila *f, Pedido p);
```

Insere um novo pedido no final da fila.

---

### 5.3 Remoção da Fila (dequeue)

```c
Pedido dequeue(Fila *f);
```

Remove e retorna o pedido que está no início da fila.

---

### 5.4 Verificação de Fila Vazia

```c
int filaVazia(Fila *f);
```

Verifica se a fila não possui pedidos pendentes.

---

### 5.5 Geração de Pedidos

```c
Pedido gerarPedido();
```

Cria pedidos aleatórios entre quatro tipos de comida:

* Hambúrguer
* Pizza
* Salada
* Massa

Cada tipo possui tempo e pontuação próprios.

---

### 5.6 Simulação de Preparo

```c
void prepararPedido();
```

Simula o tempo de preparo do pedido através de uma tela de carregamento utilizando a função `sleep()`.

---

### 5.7 Exibição da Fila

```c
void mostrarFila(Fila *f);
```

Exibe todos os pedidos atualmente na fila, respeitando a ordem FIFO.

---

## 6. Lógica do Jogo

O jogo funciona em um laço principal:

1. Exibe os pedidos na fila
2. Retira o pedido da frente da fila
3. O jogador escolhe:

   * **Preparar o pedido**
   * **Pular o pedido**, que retorna ao final da fila
4. Atualiza tempo e pontuação
5. Verifica condição de vitória ou derrota

### Regras importantes:

* Preparar consome tempo e gera pontos
* Pular consome 1 unidade de tempo
* Se o tempo acabar → Game Over

---

## 7. Controle de Tempo e Pontuação

* Tempo inicial: `10`
* Cada pedido adicionado aumenta o tempo disponível
* Cada preparo reduz o tempo conforme o pedido
* A pontuação final é a soma dos pontos dos pedidos preparados

---

## 8. Conclusão

Este projeto demonstra de forma clara e prática:

* O uso da estrutura de dados **Fila**
* Aplicação do conceito FIFO em um problema real
* Organização de código em C
* Uso de estruturas, funções e controle de fluxo

O jogo apresenta um equilíbrio entre simplicidade e complexidade, sendo adequado para fins educacionais e avaliação acadêmica.

---

## 9. Compilação e Execução do Programa

O projeto é disponibilizado de duas formas, facilitando o uso tanto para usuários finais quanto para avaliadores que desejem compilar o código-fonte.

---

### 9.1 Execução via Arquivo Executável

Para facilitar a utilização, o trabalho acompanha um **arquivo executável já compilado**.

Basta executar o arquivo correspondente ao sistema operacional:

* Em sistemas Linux:

```bash
./main
```

Essa opção permite rodar o jogo imediatamente, sem necessidade de compilação prévia.

---

### 9.2 Compilação Manual do Código-Fonte

Também é fornecido o código-fonte (`fila.c`), possibilitando a compilação manual do programa.

#### Requisitos:

* Compilador **GCC** instalado
* Sistema Linux ou ambiente compatível

#### Comando de compilação:

```bash
gcc fila.c -o main
```

Após a compilação, o programa pode ser executado com:

```bash
./main
```

---


**Autores:** Pedro Henrique Castro, Ruan Ripardo, Samuel Pinheiro 

Trabalho acadêmico – Estrutura de Dados em C
