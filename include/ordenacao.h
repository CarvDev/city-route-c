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
 * Função: merge_sort.
 * Complexidade Temporal: O(n log n) no pior caso.
 * Ordena o vetor `vet` usando Merge Sort, com elementos de
 * `tam_elemento` bytes comparados por `cmp`. 
 * Retorna as estatísticas da ordenação. Falhas são indicadas por
 * `segundos < 0`; os demais campos são zerados. Use
 * `estatisticas_falharam` para validar o resultado.
 */
EstatisticasOrdenacao merge_sort(void *vet, size_t qtd_elementos,
    size_t tam_elemento, FuncaoCompara cmp);

/*
 * Função : insertion_sort
 * Complexidade Temporal : O(n²) no pior caso.
 * Ordena o vetor `vet` usando Insertion Sort, com elementos de
 * `tam_elemento` bytes comparados por `cmp`. Cada cópia de elemento
 * realizada é contabilizada como uma movimentação.
 * Retorna as estatísticas da ordenação. Falhas são indicadas por
 * `segundos < 0`; os demais campos são zerados. Use
 * `estatisticas_falharam` para validar o resultado.
 */
EstatisticasOrdenacao insertion_sort(void *vet, size_t qtd_elementos,
    size_t tam_elemento, FuncaoCompara cmp);

/*
 * Função: estatisticas_falharam.
 * Complexidade Temporal: O(1) no pior caso.
 * Verifica se uma ordenação falhou, ou seja, se `estatisticas` é NULL ou
 * se seu campo `segundos` é negativo.
 * Retorna 1 em caso de falha e 0 caso contrário.
 */
int estatisticas_falharam(const EstatisticasOrdenacao *estatisticas);

/*
 * Função: imprimir_estatisticas.
 * Complexidade Temporal: O(1) no pior caso.
 * Imprime no terminal as estatísticas de uma ordenação identificadas pelo
 * nome do algoritmo. Se `algoritmo` for NULL, usa um rótulo genérico.
 * Estatísticas com tempo negativo indicam falha e são sinalizadas na saída.
 */
void imprimir_estatisticas(const EstatisticasOrdenacao *estatisticas,
    const char *algoritmo);
