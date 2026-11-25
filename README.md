# CityRoute C

**Sistema de Logística Urbana e Gerenciamento de Pedidos**

Projeto do Semestre — Disciplina de Estrutura de Dados
Universidade Estadual de Santa Cruz (UESC) · Curso de Ciência da Computação · Semestre 2026.2
Professora: Luenne Nailam

## 1. Sobre o projeto

O **CityRoute C** é um sistema modular, escrito em **C11**, que simula uma central de distribuição urbana. Ele recebe pedidos de entrega, organiza a ordem de atendimento por prioridade, localiza os pontos de destino e mantém um histórico das entregas processadas, além de gerar relatórios ordenados e comparar o desempenho de algoritmos de ordenação.

Cada módulo utiliza a estrutura de dados mais adequada à operação que realiza:

| Estrutura / Técnica | Aplicação no sistema |
|---------------------|----------------------|
| Árvore Binária de Busca (BST) | Cadastro, exclusão, busca e percurso em-ordem dos pontos de entrega |
| Heap Binário Mínimo | Fila de prioridade dos pedidos pendentes (com desempate FIFO) |
| Lista Simplesmente Encadeada (início e fim) | Histórico de pedidos despachados com inserção O(1) ao final |
| Recursividade | Inserção, busca, exclusão, percurso em-ordem e liberação na BST |
| Insertion Sort (O(n²)) | Algoritmo quadrático utilizado na comparação de desempenho |
| Merge Sort (O(n log n)) | Ordenação dos relatórios e comparação de desempenho |

## 2. Entidades

**Ponto de Entrega (`PontoEntrega`)**

- `id_ponto` (`int`): código único na BST
- `nome_local` (`char[100]`): bairro ou localidade
- `latitude`, `longitude` (`double`): coordenadas geográficas

**Pedido de Entrega (`Pedido`)**

- `cod_rastreio` (`int`): identificador único do pedido
- `prioridade` (`int`): `1` = Expressa, `2` = VIP, `3` = Convencional
- `ordem_chegada` (`unsigned long`): contador incremental (desempate FIFO)
- `peso` (`float`): peso em kg
- `id_destino` (`int`): código de um ponto cadastrado na BST
- `valor` (`float`): valor monetário do pedido

## 3. Funcionalidades

### Módulo 1 — Pontos de Entrega (BST)

- **RF01** – Cadastrar ponto (sem códigos duplicados)
- **RF02** – Buscar ponto por código
- **RF03** – Listar pontos em ordem crescente (percurso *in-order*)
- **RF03.1** – Excluir ponto (folha, 1 filho, 2 filhos); bloqueado se houver pedidos pendentes vinculados

### Módulo 2 — Pedidos (Heap Binário Mínimo)

- **RF04** – Inserir pedido (valida se `id_destino` existe na BST)
- **RF05** – Consultar próximo pedido sem removê-lo
- **RF06** – Processar despacho (remove o topo do heap e registra no histórico com tratamento de falhas)
- **RF07** – Exibir pedidos pendentes (conforme a disposição interna do heap)

Regra de prioridade: Expressa (`1`) > VIP (`2`) > Convencional (`3`). Empate resolvido por FIFO (menor `ordem_chegada` primeiro).

### Módulo 3 — Histórico (Lista Simplesmente Encadeada)

- **RF08** – Registrar pedido processado ao final da lista em O(1)
- **RF09** – Consultar histórico completo
- **RF10** – Buscar pedido no histórico por código de rastreio

### Módulo 4 — Relatórios, Carga de Dados e Ordenação

- **RF11** – Gerar relatório ordenado com **Merge Sort** (por código de rastreio ou valor), sobre **cópia** independente do histórico
- **RF12** – Comparar **Insertion Sort** (O(n²)) × **Merge Sort** (O(n log n)): tempo (`<time.h>`), número de comparações e número de movimentações para N = 100, 1.000 e 10.000
- **RF13** – Carga inicial automatizada com pontos e pedidos de teste

## 4. Estrutura do projeto

```text
.
├── .github/
│   └── workflows/
│       └── build.yml        # CI: recusa PR com erros/warnings
├── include/                 # Cabeçalhos (.h)
│   ├── bst.h
│   ├── entrada.h
│   ├── heap.h
│   ├── historico.h
│   ├── menu.h
│   ├── ordenacao.h
│   ├── pedido.h
│   ├── relatorio.h
│   ├── sistema.h
│   ├── tipos.h
│   ├── ui_historico.h
│   ├── ui_pedido.h
│   ├── ui_ponto.h
│   ├── ui_relatorio.h
│   └── utils.h
├── src/                     # Implementações (.c)
│   ├── bst.c
│   ├── entrada.c
│   ├── heap.c
│   ├── historico.c
│   ├── main.c
│   ├── menu.c
│   ├── ordenacao.c
│   ├── pedido.c
│   ├── relatorio.c
│   ├── sistema.c
│   ├── ui_historico.c
│   ├── ui_pedido.c
│   ├── ui_ponto.c
│   └── ui_relatorio.c
├── tests/                   # Testes unitários
│   └── test_bst.c
├── .gitignore
├── AGENTS.md
├── LICENSE                  # Licença MIT
└── README.md
```
## 5. Compilação, execução e CI

**Requisitos:** compilador C com suporte a C11 (GCC ou Clang recomendados).

### Programa principal

```bash
gcc -Wall -Wextra -pedantic -std=c11 -Iinclude src/*.c -o cityroute
./cityroute
```

O programa deve compilar **sem warnings**. Para verificar vazamentos e acessos inválidos de memória:

```bash
valgrind --leak-check=full ./cityroute
# ou com sanitizers:
gcc -Wall -Wextra -pedantic -std=c11 -fsanitize=address,undefined -g -Iinclude src/*.c -o cityroute
./cityroute
```

### Testes unitários

Os testes devem ser compilados **sem** a macro `NDEBUG` (`-UNDEBUG`) para manter todas as asserções (`assert`) ativas:

```bash
gcc -Wall -Wextra -pedantic -std=c11 -g -O0 -UNDEBUG -fsanitize=address,undefined -Iinclude tests/test_bst.c src/bst.c -o test_bst
./test_bst
```

### Integração Contínua (GitHub Actions)

O repositório conta com o workflow `.github/workflows/build.yml`, executado automaticamente sempre que um **Pull Request** é aberto ou atualizado. Caso a compilação gere qualquer erro ou *warning*, o Pull Request é recusado automaticamente.

## 6. Guia de uso

Após compilar (seção 5), execute `./cityroute`. O programa abre no **Menu Principal**:

```text
1 - Pontos de Entrega
2 - Pedidos
3 - Histórico
4 - Relatórios
5 - Ajuda
0 - Sair
```

Digite o número da opção e pressione `ENTER`. Em qualquer submenu, `0` volta ao menu principal; no menu principal, `0` encerra o programa e libera a memória. Após cada operação, a mensagem `Pressione ENTER para continuar...` exige um `ENTER` extra. Opções inválidas exibem um aviso e retornam ao menu.

### Fluxo recomendado

1. Cadastre pontos de entrega (módulo 1): um pedido só é aceito se o `id_destino` existir.
2. Insira pedidos (módulo 2): a fila atende primeiro a menor prioridade numérica (Expressa `1` > VIP `2` > Convencional `3`), com desempate por ordem de chegada (FIFO).
3. Processe o despacho (módulo 2, opção `3`) para remover o pedido do heap e registrá-lo no histórico.
4. Consulte o histórico (módulo 3) e gere relatórios ou compare algoritmos (módulo 4).

### Dados digitados

| Campo | Formato e validação |
|-------|---------------------|
| Opções, IDs, códigos e prioridade | Inteiros, um por linha; prioridade aceita somente `1`, `2` ou `3` |
| Nome do local | Texto não vazio de até 99 caracteres (aceita acentos) |
| Latitude e longitude | Números decimais finitos, com `.` como separador (ex.: `-14.8167`) |
| Peso (kg) | Decimal finito maior que `0` |
| Valor (R$) | Decimal finito maior ou igual a `0` |
| Código de rastreio | Inteiro único: não pode repetir entre pendentes nem no histórico |

### Módulo 1 — Pontos de Entrega

| Opção | Entradas | Resultado |
|-------|----------|-----------|
| `1` Cadastrar ponto | `ID do ponto`, `Nome do local`, `Latitude`, `Longitude` | Insere na BST; ID repetido é recusado |
| `2` Buscar ponto por código | `ID do ponto` | Exibe ID, nome e coordenadas, ou aviso de não encontrado |
| `3` Listar pontos em ordem | — | Percurso *in-order*: IDs em ordem crescente |
| `4` Excluir ponto | `ID do ponto` | Remove o nó; recusado se houver pedido pendente com esse destino |

### Módulo 2 — Pedidos

| Opção | Entradas | Resultado |
|-------|----------|-----------|
| `1` Inserir pedido | `Código de rastreio`, `Prioridade`, `ID do destino`, `Peso (kg)`, `Valor (R$)` | Entra no heap se o destino existir e o rastreio for único |
| `2` Consultar próximo pedido | — | Mostra o topo do heap sem removê-lo |
| `3` Processar despacho | — | Remove o topo e o registra no histórico; se o registro falhar, o pedido permanece pendente |
| `4` Exibir pedidos pendentes | — | Mostra a disposição interna do heap (que não é a ordem de despacho) |

### Módulo 3 — Histórico

| Opção | Entradas | Resultado |
|-------|----------|-----------|
| `1` Consultar histórico completo | — | Lista somente os pedidos já despachados |
| `2` Buscar pedido por código de rastreio | `Código de rastreio` | Exibe o pedido ou aviso de não encontrado |

### Módulo 4 — Relatórios

| Opção | Entradas | Resultado |
|-------|----------|-----------|
| `1` Relatório ordenado | Critério: `1` por rastreio ou `2` por valor | Lista o histórico ordenado com Merge Sort, sem alterá-lo |
| `2` Comparar algoritmos de ordenação | Critério: `1` por rastreio ou `2` por valor | Mostra tempo, comparações e movimentações de Insertion Sort e Merge Sort sobre o histórico atual |
| `3` Carga inicial automatizada | Confirmação `S/N` (se já houver dados) e quantidade: `1` = 100, `2` = 1.000, `3` = 10.000 | **Apaga os dados atuais** e gera `N` pontos e `2N` pedidos, dos quais `N` já são despachados |

A carga é a forma mais rápida de preparar a comparação do RF12: com `1` = 100, por exemplo, o histórico passa a ter exatamente 100 pedidos.

### Manual de ajuda

O manual com uso, opções, módulos, navegação e regras de entrada pode ser consultado de duas formas:

- **Pelo menu interativo:** escolha `5 - Ajuda` no Menu Principal. O texto é exibido e, após o `ENTER` da pausa, o menu principal retorna.
- **Pela linha de comando:** sem abrir o menu, execute:

```bash
./cityroute --help
./cityroute -h
```

As duas opções de linha de comando terminam com código de saída `0`. Qualquer outro argumento (ou quantidade inválida de argumentos) exibe uma mensagem de erro, terminando com código `1`. Sem argumentos, o programa inicia normalmente.

## 7. Requisitos técnicos

- **C11** (ISO/IEC 9899:2011), modularizado em arquivos `.h` e `.c`
- Alocação dinâmica obrigatória; **proibido** usar vetores estáticos para estruturas dinâmicas
- Toda memória alocada deve ser liberada (ao remover nós e ao encerrar o programa)
- BST com nós encadeados e operações **recursivas** (inserção, busca, remoção, percurso e liberação)
- Heap binário mínimo e algoritmos de ordenação implementados pelos próprios estudantes
- Validação rigorosa de entradas, ponteiros nulos, overflow numérico e falhas de alocação
- *Segmentation Fault* resulta em penalização
- Cada função declarada em `.h` deve ter comentário com a **complexidade temporal no pior caso**. Exemplo (`include/bst.h`):

```c
/*
 * Realiza a busca recursiva de um ponto de entrega pelo seu id_ponto.
 * Explora as propriedades da BST (menores a esquerda, maiores a direita).
 * Retorna ponteiro constante para o no correspondente ou NULL se nao existir.
 *
 * O(n) pior: busca recursiva por id_ponto.
 */
const NoBST *bst_buscar(const NoBST *raiz, int id_ponto);
```

## 8. Etapas e avaliação

| Etapa | Data | Entrega | Peso |
|-------|------|---------|------|
| 1. Modelagem e TADs | 23/11 | PDF com requisitos, protótipo das structs e arquivos `.h` com complexidades comentadas | 15% |
| 2. Implementação e Integração | 03/12 | Código-fonte funcional e modularizado com menu interativo integrando BST, Heap e Histórico | 45% |
| 3. Testes, Relatório e Defesa Oral | 07/12 | Testes unitários, relatório técnico em PDF e apresentação no laboratório com perguntas individuais | 40% |

## 9. Análise de desempenho (a preencher)

| N | Algoritmo | Tempo (s) | Comparações | Movimentações |
|-----|-----------|-----------|-------------|---------------|
| 100 | Insertion Sort (O(n²)) | | | |
| 100 | Merge Sort (O(n log n)) | | | |
| 1.000 | Insertion Sort (O(n²)) | | | |
| 1.000 | Merge Sort (O(n log n)) | | | |
| 10.000 | Insertion Sort (O(n²)) | | | |
| 10.000 | Merge Sort (O(n log n)) | | | |

## 10. Checklist

### Etapa 1: Modelagem e TADs (15% da Nota) - 23/11

- [x] Documento em PDF com o levantamento de requisitos
- [x] Complexidade comentada em todas as funções dos `.h`
- [x] Protótipo das structs e outros tipos de dados derivados

### Etapa 2: Implementação e Integração (45% da Nota) - 03/12

- [x] BST: inserir, buscar, listar (*in-order*), excluir (3 casos) e liberar, tudo recursivo
- [x] Exclusão de ponto bloqueada se houver pedidos pendentes
- [x] Heap com prioridade + desempate FIFO
- [x] Validação de `id_destino` ao inserir pedido
- [x] Despacho de pedidos (extração do heap + registro seguro no histórico)
- [x] Histórico com registro, listagem e busca por código
- [x] Ordenação O(n²) e O(n log n) sobre cópias dos dados
- [x] Carga automática de dados de teste

### Etapa 3: Testes, Relatório e Defesa Oral (40% da Nota) - 07/12

- [ ] Suíte completa de testes unitários
  - [x] Teste unitário: BST
  - [ ] Teste unitário: Heap
  - [ ] Teste unitário: Histórico
  - [ ] Teste unitário: Ordenação e Relatórios
- [ ] Sem warnings, sem segfaults, sem vazamentos de memória
  - [x] Validado no teste geral interativo
  - [ ] Validado nos testes unitários
- [x] Manual de uso e execução no `README.md`
- [ ] Relatório técnico em PDF
- [ ] Comparação de algoritmos para N = 100, 1.000 e 10.000 documentada
- [ ] Demonstração prática no laboratório com perguntas individuais para os membros da equipe

### Opcionais

- [ ] QA interno
- [ ] Makefile ou CMake
  - [ ] Compilação padrão otimizada (`all`)
  - [ ] Compilação de depuração (`debug`)
  - [ ] Testes individuais (`test-bst`, `test-heap`, `test-historico`, `test-ordenacao`)
  - [ ] Alvo agregador de testes (`test`)
  - [ ] Limpeza (`clean`)
- [x] Manual em CLI com `--help`
- [ ] Detalhar feedback e mensagens de erro
- [ ] Interface gráfica

## 11. Autoria

- Amanda Cardoso Lopes ([4mandaCardoso](https://github.com/4mandaCardoso))
- André Felipe Oliveira Xavier ([Felipzzk](https://github.com/Felipzzk))
- Arthur de Carvalho Lima ([CarvDev](https://github.com/CarvDev))
- Rafael Mota Freitas ([rafaelmotafreitas](https://github.com/rafaelmotafreitas))

## 12. Licença

Este projeto está licenciado sob a [**MIT License**](LICENSE).
