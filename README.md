# CityRoute C

**Sistema de Logística Urbana e Gerenciamento de Pedidos**

Projeto do Semestre — Disciplina de Estrutura de Dados
Universidade Estadual de Santa Cruz (UESC) · Curso de Ciência da Computação · Semestre 2026.2
Professora: Luenne Nailam

## 1. Sobre o projeto

O **CityRoute C** é um sistema simplificado, escrito em **C**, que simula uma central de distribuição urbana. Ele recebe pedidos de entrega, organiza a ordem de atendimento por prioridade, localiza os pontos de destino e mantém um histórico das entregas processadas, além de gerar relatórios ordenados e comparar o desempenho de algoritmos de ordenação.

Cada módulo utiliza a estrutura de dados mais adequada à operação que realiza:

| Estrutura / Técnica | Aplicação no sistema |
|---------------------|----------------------|
| Árvore Binária de Busca (BST) | Cadastro, exclusão, busca e percurso dos pontos de entrega |
| Heap Binário | Fila de prioridade dos pedidos pendentes |
| Lista Encadeada / Vetor Dinâmico | Histórico de pedidos despachados |
| Recursividade | Inserção, busca, exclusão e percurso na BST |
| Algoritmo O(n²) | Ordenação do relatório (Bubble, Insertion ou Selection Sort) |
| Algoritmo O(n log n) | Ordenação de alto desempenho (Quick ou Merge Sort) |

## 2. Entidades

**Ponto de Entrega**

- `id_ponto` (int): código único
- `nome_local` (string): bairro ou localidade
- `latitude`, `longitude` (double): coordenadas geográficas

**Pedido de Entrega**

- `cod_rastreio` (int ou string): identificador único
- `prioridade` (int): 1 = Expressa, 2 = VIP, 3 = Convencional
- `ordem_chegada` (unsigned long): contador incremental (desempate FIFO)
- `peso` (float): peso em kg
- `id_destino` (int): código de um ponto cadastrado
- `valor` (float): valor monetário do pedido

## 3. Funcionalidades

### Módulo 1 — Pontos de Entrega (BST)

- **RF01** – Cadastrar ponto (sem códigos duplicados)
- **RF02** – Buscar ponto por código
- **RF03** – Listar pontos em ordem crescente (percurso *in-order*)
- **RF03.1** – Excluir ponto (folha, 1 filho, 2 filhos); bloqueado se houver pedidos pendentes vinculados

### Módulo 2 — Pedidos (Heap / Fila de Prioridade)

- **RF04** – Inserir pedido (valida se `id_destino` existe na BST)
- **RF05** – Consultar próximo pedido sem removê-lo
- **RF06** – Processar despacho (remove o topo do heap e registra no histórico)
- **RF07** – Exibir pedidos pendentes (conforme a estrutura do heap)

Regra de prioridade: Expressa > VIP > Convencional. Empate resolvido por FIFO (menor `ordem_chegada` primeiro).

### Módulo 3 — Histórico (Lista Encadeada ou Vetor Dinâmico)

- **RF08** – Registrar pedido processado
- **RF09** – Consultar histórico completo
- **RF10** – Buscar pedido no histórico por código de rastreio

### Módulo 4 — Relatórios, Carga de Dados e Ordenação

- **RF11** – Relatório ordenado (por código de rastreio ou valor), sobre **cópia** do histórico
- **RF12** – Comparar algoritmos O(n²) × O(n log n): tempo (`<time.h>`) e nº de comparações/trocas para N = 100, 1.000 e 10.000
- **RF13** – Carga inicial automatizada com dados aleatórios para testes de estresse

## 4. Compilação e execução

Requisitos: compilador C (GCC ou Clang)

```bash
gcc -Wall -Wextra -pedantic -std=c11 -Iinclude src/*.c -o cityroute
./cityroute
```

O programa deve compilar **sem warnings**. Para verificar vazamentos e acessos inválidos de memória:

```bash
valgrind --leak-check=full ./cityroute
# ou
gcc -fsanitize=address,undefined -g -Iinclude src/*.c -o cityroute
```

## 5. Requisitos técnicos

- C ANSI, modularizado em arquivos `.h` e `.c`
- Alocação dinâmica obrigatória; **proibido** usar vetores estáticos para estruturas dinâmicas
- Toda memória alocada deve ser liberada (ao remover nós e ao encerrar o programa)
- BST com nós encadeados e operações **recursivas** (inserção, busca, remoção, percurso)
- Heap e algoritmos de ordenação implementados pelos próprios estudantes
- Segmentation Fault resulta em penalização
- Cada função declarada em `.h` deve ter comentário com a **complexidade temporal no pior caso**. Ex:

```c
/*
 * Funcao : buscar_ponto
 * Complexidade Temporal : O(log n) medio / O(n) pior caso
 * Retorna o ponteiro para o no do ponto de entrega.
 */
NoBST *buscar_ponto(NoBST *raiz, int id_ponto);
```

## 6. Etapas e avaliação

| Etapa | Entrega | Peso |
|-------|---------|------|
| 1. Modelagem e TADs | PDF com requisitos, protótipo das structs e arquivos `.h` com complexidades comentadas | 15% |
| 2. Implementação e Integração | Código-fonte funcional e modularizado com menu interativo integrando BST, Heap e Histórico | 45% |
| 3. Testes, Relatório e Defesa Oral | Relatório técnico em PDF (gráficos/tabelas de desempenho e análise Big-O) + apresentação no laboratório em **07/12**, com perguntas individuais | 40% |

## 7. Análise de desempenho (preencher na Etapa 3)

| N | Algoritmo | Tempo (s) | Comparações | Trocas |
|---|-----------|-----------|-------------|--------|
| 100 | O(n²) | | | |
| 100 | O(n log n) | | | |
| 1.000 | O(n²) | | | |
| 1.000 | O(n log n) | | | |
| 10.000 | O(n²) | | | |
| 10.000 | O(n log n) | | | |

## 8. Checklist

- [ ] BST: inserir, buscar, listar (in-order) e excluir (3 casos), tudo recursivo
- [ ] Exclusão de ponto bloqueada se houver pedidos pendentes
- [ ] Heap com prioridade + desempate FIFO
- [ ] Validação de `id_destino` ao inserir pedido
- [ ] Histórico com registro, listagem e busca por código
- [ ] Ordenação O(n²) e O(n log n) sobre cópias dos dados
- [ ] Comparação de algoritmos para N = 100, 1.000 e 10.000
- [ ] Carga automática de dados de teste
- [ ] Complexidade comentada em todas as funções dos `.h`
- [ ] Sem warnings, sem segfaults, sem vazamentos de memória
- [ ] Relatório técnico em PDF

## 9. Autoria

- Arthur de Carvalho ([CarvDev](https://github.com/CarvDev))
- Amanda Cardoso ([4mandaCardoso](https://github.com/4mandaCardoso))
- Rafael Mota ([rafaelmotafreitas](https://github.com/rafaelmotafreitas))
- Felipe Oliveira ([Felipzzk](https://github.com/Felipzzk))
