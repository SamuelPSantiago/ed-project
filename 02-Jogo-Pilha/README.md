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

### 4.1 Estrutura Pilha

```c
typedef struct {
    int elementos[10];
    int topo;
} Pilha;
```

A pilha é implementada usando um vetor estático, controlado por um índice:

* elementos: armazena os elementos mágicos
* topo: indica a posição do último elemento inserido

---

## 5. Funções Principais

### 5.1 Inicialização da Pilha

```c
void inicializarPilha(Pilha *p);
```

Inicializa a pilha, definindo topo como -1.

---

### 5.2 Empilhar Elemento (push)

```c
void push(Pilha *p, int elemento);
```

Insere um novo elemento mágico no topo da pilha.

---

### 5.3 Desempilhar Elemento (pop)

```c
int pop(Pilha *p);
```
Remove e retorna o elemento que está no topo da pilha.

---

### 5.4 Verificação de Pilha Vazia

```c
int pilhaVazia(Pilha *p);
```

Verifica se a pilha está vazia.

---

### 5.5 Limpeza da Pilha

```c
void limparPilha(Pilha *p);
```

Remove todos os elementos da pilha, retornando-a ao estado inicial.

---

### 5.6 Conjuração de Magias

```c
void conjurarMagia(Pilha *p);
```

Utiliza os dois elementos do topo da pilha para tentar formar uma magia.

A ordem dos elementos não interfere na conjuração, permitindo combinações como Fogo + Ar ou Ar + Fogo.

---

## 6. Lógica do Jogo

O jogo funciona em um laço principal:

1. Limpa a tela e exibe apenas as informações essenciais
2. Mostra o estado atual da pilha
3. O jogador escolhe:

    * Empilhar um elemento
    * Conjurar uma magia
4. Limpar a pilha
5. Sair

* O sistema verifica se a magia é eficaz
* Atualiza o número de tentativas
* Verifica condição de vitória ou derrota

### Regras importantes:

* Cada conjuração consome dois elementos da pilha
* A ordem dos elementos não importa
* Magias corretas avançam no combate
* Magias incorretas consomem tentativas

---

## 8. Conclusão

Este projeto demonstra de forma clara e prática:

* O uso da estrutura de dados Pilha
* Aplicação do conceito LIFO em um problema real
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

Também é fornecido o código-fonte (`pilha.c`), possibilitando a compilação manual do programa.

#### Requisitos:

* Compilador **GCC** instalado
* Sistema Linux ou ambiente compatível

#### Comando de compilação:

```bash
gcc pilha.c -o main
```

Após a compilação, o programa pode ser executado com:

```bash
./main
```

---

**Autores:** Pedro Henrique Castro, Ruan Ripardo, Samuel Pinheiro 

Trabalho acadêmico – Estrutura de Dados em C