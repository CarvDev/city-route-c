# AGENTS.md

Diretrizes para agentes que trabalharem neste repositório.

## Visão geral

**CityRoute C** é um sistema de logística urbana em C11, modularizado
em `include/` (cabeçalhos) e `src/` (implementações). As estruturas principais
são uma BST de pontos de entrega, um heap de pedidos, um histórico de pedidos
despachados e algoritmos de ordenação O(n²) e O(n log n).

Consulte `README.md` para requisitos, entidades e funcionalidades.

## Comandos

Compilação (mesmo comando do CI, com `-Werror`):

```bash
gcc -Wall -Wextra -pedantic -std=c11 -Werror -Iinclude src/*.c -o cityroute
```

Testes da BST (não há runner genérico; compile e execute manualmente):

```bash
gcc -Wall -Wextra -pedantic -std=c11 -Werror -Iinclude src/bst.c tests/test_bst.c -o /tmp/test_bst
/tmp/test_bst
```

Verificação de memória:

```bash
valgrind --leak-check=full --error-exitcode=99 ./cityroute < entrada.txt
# ou
gcc -fsanitize=address,undefined -g -Iinclude src/*.c -o cityroute
```

O CI (`.github/workflows/build.yml`) exige compilação sem warnings em pull
requests para `main`. Rode o comando de compilação antes de finalizar
qualquer alteração.

Os testes usam assert. Nunca compilá-los com -DNDEBUG.

## Estrutura

- `include/`: declarações e documentação das funções.
- `src/`: implementações e menus (`ui_*.c`).
- `tests/`: testes unitários (ex.: `test_bst.c`).
- `cityroute`: binário gerado; já está no `.gitignore`.

## Regras e Convenções

- C11, com alocação dinâmica obrigatória para estruturas que crescem:
  - **Não** use vetores estáticos para estruturas dinâmicas, como
    nós, heap, histórico e vetores de ordenação.
  - Vetores estáticos são permitidos para campos de tamanho fixo, como
    nome_local[100] e buf[64].
- Toda memória alocada deve ser liberada (inclusive ao encerrar o programa).
- Operações da BST (`bst.c`) devem ser recursivas: inserção, busca,
  remoção e percurso.
- Mantenha a modularização: cabeçalhos em `include/`, implementação em `src/`.
- Use nomes em português, seguindo o padrão existente:
  - funções e variáveis: `snake_case`
  - tipos/structs: `PascalCase`
  - constantes/macros: `UPPER_CASE`
- Comentários e mensagens ao usuário são em português, com acentos UTF-8.
- Cada função declarada em um `.h` deve ter comentário com a complexidade
  temporal no pior caso e o contrato da função.
- Não introduza `segfaults`, warnings ou vazamentos: valide com compilação
  estrita e, quando conveniente, `valgrind`/sanitizers.
- Sem castings no retorno de malloc/calloc.   
- sistema.c guarda as regras de negócio e não lê do teclado nem imprime.
- Os TADs não devem realizar I/O por conta própria, no entanto podem 
  implementar funções de I/O para serem chamadas em ui_*.c.
- heap e ordenações são feitos pela equipe, sem qsort, bsearch ou 
  bibliotecas de fila. 
- O relatório (RF11) ordena sempre uma cópia, sem alterar o histórico.
- Convenções de retorno:
  - bool é proibido. 1 significa sucesso e 0 falha.
  - Ponteiros NULL indicam falha de alocação.
- float/double devem ser verificados com isfinite na entrada.

## Estado atual / cuidados

- O menu principal integra os módulos, mas parte das funcionalidades ainda
  está como stub (ações `NULL` em `ui_pedido.c`, `ui_historico.c` e na carga
  automática de `ui_relatorio.c`).
- Não marque itens no checklist do `README.md` sem implementar e verificar o
  comportamento correspondente.
- Só faça commit/push quando explicitamente solicitado.
