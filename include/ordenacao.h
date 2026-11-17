#pragma once

#include <stddef.h>
#include "tipos.h"

/*
 * Define a função de comparação usada pelo algoritmo de ordenação.
 * Deve retornar um valor negativo, zero ou positivo quando o primeiro
 * elemento for, respectivamente, menor, igual ou maior que o segundo.
 */
typedef int (*FuncaoCompara)(const void *, const void *);

/*
 * Função : merge_sort
 * Complexidade Temporal : O(n log n) comparações e movimentações
 * Complexidade Espacial : O(n) para o vetor auxiliar
 * Ordena o vetor `arr` usando Merge Sort, com elementos de
 * `tam_elemento` bytes comparados por `cmp`. 
 * Retorna as estatísticas da ordenação. Em caso de falha de alocação,
 * comparacoes, movimentacoes e segundos são definidos como -1.
 */
EstatisticasOrdenacao merge_sort(void *arr, size_t qtd_elementos,
    size_t tam_elemento, FuncaoCompara cmp);
