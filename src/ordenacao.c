#include "tipos.h"
#include "ordenacao.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Etapa merge do Merge Sort
// Ordena os elementos no vetor auxiliar e depois envia de volta para o original
static void merge(unsigned char *base, unsigned char *aux, size_t tam, size_t esq,
    size_t meio, size_t dir, FuncaoCompara cmp, EstatisticasOrdenacao *ptrEstatistica) 
{
    size_t i = esq, j = meio + 1, k = 0;

    // Copia os elementos do vetor base pro auxiliar, ordenando-os 
    while (i <= meio && j <= dir) {
        if (cmp(base + i * tam, base + j * tam) <= 0)
            memcpy(aux + k++ * tam, base + i++ * tam, tam);
        else
            memcpy(aux + k++ * tam, base + j++ * tam, tam);
        ptrEstatistica->movimentacoes++;
        ptrEstatistica->comparacoes++;
    }

    // Copia os elementos restantes, se houverem
    while (i <= meio) {
        memcpy(aux + k++ * tam, base + i++ * tam, tam);
        ptrEstatistica->movimentacoes++;
    }
    while (j <= dir) {
        memcpy(aux + k++ * tam, base + j++ * tam, tam);
        ptrEstatistica->movimentacoes++;
    }

    // Sobrescreve o vetor original com o vetor ordenado
    memcpy(base + esq * tam, aux, k * tam);
    ptrEstatistica->movimentacoes += (k * tam);
}

// Etapa de divisão do Merge Sort 
// Divide o vetor recursivamente em múltiplos subvetores
// Chama a etapa merge quando o caso base é alcançado
static void merge_sort_rec(unsigned char *base, unsigned char *aux, size_t tam,
    size_t esq, size_t dir, FuncaoCompara cmp, EstatisticasOrdenacao *ptrEstatistica)
{
    if (esq >= dir) return; // Caso base
    size_t meio = esq + (dir - esq) / 2;

    merge_sort_rec(base, aux, tam, esq, meio, cmp, ptrEstatistica);
    merge_sort_rec(base, aux, tam, meio + 1, dir, cmp, ptrEstatistica);
    merge(base, aux, tam, esq, meio, dir, cmp, ptrEstatistica);
}
    
EstatisticasOrdenacao merge_sort(void *arr, size_t qtd_elementos, size_t tam_elemento, FuncaoCompara cmp) {
    size_t tam_total = qtd_elementos * tam_elemento;
    if (tam_elemento < 2) return (EstatisticasOrdenacao){0};

    unsigned char *aux = malloc(tam_total);
    if (aux == NULL) return (EstatisticasOrdenacao){ .comparacoes = -1, .movimentacoes = -1, .segundos = -1 };

    EstatisticasOrdenacao estatisticas = {0};
    clock_t inicio = clock();
    merge_sort_rec(arr, aux, tam_elemento, 0, qtd_elementos - 1, cmp, &estatisticas);
    free(aux);

    clock_t fim = clock();
    estatisticas.segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return estatisticas;
}