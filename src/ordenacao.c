#include "tipos.h"
#include "utils.h"
#include "ordenacao.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Etapa merge do Merge Sort
// Ordena os elementos no vetor auxiliar e depois envia de volta para o original
static void merge(unsigned char *base, unsigned char *aux, size_t tam, size_t esq,
    size_t meio, size_t dir, FuncaoCompara cmp, EstatisticasOrdenacao *ptr_estatistica) 
{
    size_t i = esq, j = meio + 1, k = 0;

    // Copia os elementos do vetor base pro auxiliar, ordenando-os 
    while (i <= meio && j <= dir) {
        if (cmp(base + i * tam, base + j * tam) <= 0)
            memcpy(aux + k++ * tam, base + i++ * tam, tam);
        else
            memcpy(aux + k++ * tam, base + j++ * tam, tam);
        ptr_estatistica->movimentacoes++;
        ptr_estatistica->comparacoes++;
    }

    // Copia os elementos restantes, se houverem
    while (i <= meio) {
        memcpy(aux + k++ * tam, base + i++ * tam, tam);
        ptr_estatistica->movimentacoes++;
    }
    while (j <= dir) {
        memcpy(aux + k++ * tam, base + j++ * tam, tam);
        ptr_estatistica->movimentacoes++;
    }

    // Sobrescreve o vetor original com o vetor ordenado
    memcpy(base + esq * tam, aux, k * tam);
    ptr_estatistica->movimentacoes += k;
}

// Etapa de divisão do Merge Sort 
// Divide o vetor recursivamente em múltiplos subvetores
// Chama a etapa merge quando o caso base é alcançado
static void merge_sort_rec(unsigned char *base, unsigned char *aux, size_t tam,
    size_t esq, size_t dir, FuncaoCompara cmp, EstatisticasOrdenacao *ptr_estatistica)
{
    if (esq >= dir) return; // Caso base
    size_t meio = esq + (dir - esq) / 2;

    merge_sort_rec(base, aux, tam, esq, meio, cmp, ptr_estatistica);
    merge_sort_rec(base, aux, tam, meio + 1, dir, cmp, ptr_estatistica);
    merge(base, aux, tam, esq, meio, dir, cmp, ptr_estatistica);
}
    
EstatisticasOrdenacao merge_sort(void *vet, size_t qtd_elementos, 
    size_t tam_elemento, FuncaoCompara cmp) 
{
    if (qtd_elementos < 2 || tam_elemento < 1) 
        return (EstatisticasOrdenacao){0};

    if (vet == NULL || cmp == NULL || mul_estoura_size(qtd_elementos, tam_elemento))
        return (EstatisticasOrdenacao){ .segundos = -1 };

    unsigned char *aux = malloc(qtd_elementos * tam_elemento);
    if (aux == NULL) 
        return (EstatisticasOrdenacao){ .segundos = -1 };
    
    EstatisticasOrdenacao estatisticas = {0};
    clock_t inicio = clock();
    merge_sort_rec(vet, aux, tam_elemento, 0, qtd_elementos - 1, cmp, &estatisticas);
    free(aux);

    clock_t fim = clock();
    estatisticas.segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return estatisticas;
}

EstatisticasOrdenacao insertion_sort(void *vet, size_t qtd_elementos,
    size_t tam_elemento, FuncaoCompara cmp)
{
    if (qtd_elementos < 2 || tam_elemento < 1) 
        return (EstatisticasOrdenacao){0};

    if (vet == NULL || cmp == NULL || mul_estoura_size(qtd_elementos, tam_elemento))
        return (EstatisticasOrdenacao){ .segundos = -1 };

    unsigned char *base = vet;
    unsigned char *chave = malloc(tam_elemento);
    if (chave == NULL)
        return (EstatisticasOrdenacao){ .segundos = -1 };

    EstatisticasOrdenacao estatisticas = {0};
    clock_t inicio = clock();

    for (size_t i = 1; i < qtd_elementos; i++) {
        // Copia a chave
        memcpy(chave, base + i * tam_elemento, tam_elemento);
        estatisticas.movimentacoes++;

        size_t j = i;
        while (j > 0) {
            estatisticas.comparacoes++;
            if (cmp(base + (j - 1) * tam_elemento, chave) <= 0) break;

            memcpy(base + j * tam_elemento, base + (j - 1) * tam_elemento, tam_elemento);
            estatisticas.movimentacoes++;
            j--;
        }

        memcpy(base + j * tam_elemento, chave, tam_elemento);
        estatisticas.movimentacoes++;
    }

    free(chave);

    clock_t fim = clock();
    estatisticas.segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return estatisticas;
}

int estatisticas_falharam(const EstatisticasOrdenacao *estatisticas) {
    return estatisticas == NULL || estatisticas->segundos < 0;
}

void imprimir_estatisticas(const EstatisticasOrdenacao *estatisticas, const char *algoritmo) {
    const char *nome = (algoritmo != NULL) ? algoritmo : "Algoritmo não informado";

    puts(LINHA_PADRAO);
    printf("Estatísticas: %s\n", nome);
    puts(LINHA_PADRAO);

    if (estatisticas_falharam(estatisticas)) {
        printf("Ordenação não concluída.\n");
        puts(LINHA_PADRAO);
        return;
    }

    printf("Comparações     : %lu\n", estatisticas->comparacoes);
    printf("Movimentações   : %lu\n", estatisticas->movimentacoes);
    printf("Tempo (s)       : %.6f\n", estatisticas->segundos);
    puts(LINHA_PADRAO);
}
