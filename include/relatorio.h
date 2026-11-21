#pragma once

#include <stddef.h>
#include "tipos.h"
#include "ordenacao.h"

/*
 * Função: gerar_relatorio_ordenado.
 * Complexidade Temporal: O(n log n) no pior caso, onde n é a quantidade de pedidos.
 * Copia os pedidos de `hist` para um vetor, ordena pelo critério `c` com
 * Merge Sort e grava a quantidade de elementos em `ptr_tam`.
 * O histórico original não é modificado. O chamador é responsável por
 * liberar o vetor retornado com free().
 * Retorna NULL se os argumentos forem inválidos, o critério não existir ou
 * a alocação falhar.
 */
Pedido *gerar_relatorio_ordenado(const Historico *hist, Criterio c, size_t *ptr_tam);

/*
 * Função: get_funcao_cmp.
 * Complexidade Temporal: O(1) no pior caso.
 * Retorna a função de comparação correspondente ao critério `c`
 * (`POR_RASTREIO` ou `POR_VALOR`).
 * Retorna NULL se o critério for inválido.
 */
FuncaoCompara get_funcao_cmp(Criterio c);

/*
 * Função: comparar_ordenacoes.
 * Complexidade Temporal: O(n²) no pior caso, dominado pelo Insertion Sort.
 * Ordena duas cópias de `vet_base`, uma com Insertion Sort e outra com
 * Merge Sort, usando o critério `c`, e grava as estatísticas em
 * `ptr_status_insert` e `ptr_status_merge`. O vetor original não é modificado.
 * Use `estatisticas_falharam()` para verificar se alguma ordenação falhou.
 * Se algum ponteiro de entrada for NULL, a função não faz nada.
 * Se o critério `c` for inválido, gera falha (`segundos` definidos como -1).
 */
void comparar_ordenacoes(const Pedido *vet_base, size_t tam, Criterio c,
    EstatisticasOrdenacao *ptr_status_insert, EstatisticasOrdenacao *ptr_status_merge);
