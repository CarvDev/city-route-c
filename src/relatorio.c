#include "relatorio.h" 
#include "ordenacao.h"
#include "tipos.h"
#include "historico.h" 
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// Para comparar pelo código de rastreio
static int compara_cod_rastreio(const void *a, const void *b) {
    const Pedido *p1 = (const Pedido*)a;
    const Pedido *p2 = (const Pedido*)b;

    return (p1->cod_rastreio > p2->cod_rastreio) - 
        (p1->cod_rastreio < p2->cod_rastreio);
}

// Para comparar pelo valor
static int compara_valor(const void *a, const void *b) {
    const Pedido *p1 = (const Pedido *)a;
    const Pedido *p2 = (const Pedido *)b;

    /*
      Obs: o código abaixo encerra a execução do programa 
      com erro caso um dos floats seja NaN ou infinito, 
      somente ao compilar para testes. Ao compilar para 
      produção com a flag `-DNDEBUG`, essas instruções são
      eliminadas do código, deixando a função mais leve.
      
      Na versão de produção, espera-se que quem chama
      essa função já tenha validado os floats.
    */
    assert(isfinite(p1->valor) && "p1->valor invalido (NaN ou Inf)");
    assert(isfinite(p2->valor) && "p2->valor invalido (NaN ou Inf)");

    return (p1->valor > p2->valor) - (p1->valor < p2->valor);
}

// Obtém a função de comparação com base no critério fornecido
FuncaoCompara get_funcao_cmp(Criterio c) {
    FuncaoCompara funcs[] = {
        [POR_RASTREIO] = compara_cod_rastreio,
        [POR_VALOR] = compara_valor
    };
    const size_t qtd_funcoes = sizeof(funcs) / sizeof(FuncaoCompara);

    if ((size_t)c >= qtd_funcoes) return NULL;
    return funcs[c];
}

// Interface para executar merge_sort no vetor de pedidos
static EstatisticasOrdenacao m_sort_pedidos(Pedido *vet, Criterio c, size_t qtd_elementos) {
    return merge_sort(vet, qtd_elementos, sizeof(Pedido), get_funcao_cmp(c));
}

// Interface para executar insertion_sort no vetor de pedidos
static EstatisticasOrdenacao i_sort_pedidos(Pedido *vet, Criterio c, size_t qtd_elementos) {
    return insertion_sort(vet, qtd_elementos, sizeof(Pedido), get_funcao_cmp(c));
}

Pedido *gerar_relatorio_ordenado(const Historico *hist, Criterio c, size_t *ptr_tam) {
    FuncaoCompara cmp = get_funcao_cmp(c);
    if (cmp == NULL) return NULL;
    
    Pedido *vet_relatorio = historico_copiar(hist, ptr_tam);
    if (vet_relatorio == NULL) return NULL;
    
    EstatisticasOrdenacao e = m_sort_pedidos(vet_relatorio, c, *ptr_tam);
    if (estatisticas_falharam(&e)) {
        free(vet_relatorio);
        return NULL;
    }

    return vet_relatorio;
}

void comparar_ordenacoes(const Pedido *vet_base, size_t tam, Criterio c,
    EstatisticasOrdenacao *ptr_status_insert, EstatisticasOrdenacao *ptr_status_merge)
{
    if (vet_base == NULL || ptr_status_insert == NULL || ptr_status_merge == NULL) return;

    if (mul_estoura_size(tam, sizeof(Pedido))) {
        *ptr_status_insert = (EstatisticasOrdenacao){.segundos = -1};
        *ptr_status_merge  = (EstatisticasOrdenacao){.segundos = -1};
        return;
    }
    const size_t tam_bytes = tam * sizeof(Pedido);
    Pedido *vet_merge = malloc(tam_bytes);
    Pedido *vet_insert = malloc(tam_bytes);

    unsigned char erro_alocacao = 0;
    erro_alocacao |= (vet_merge == NULL);
    erro_alocacao |= (vet_merge == NULL);

    if (erro_alocacao) {
        *ptr_status_insert = (EstatisticasOrdenacao){.segundos = -1};
        *ptr_status_merge = (EstatisticasOrdenacao){.segundos = -1};
        free(vet_merge);
        free(vet_insert);
        return;
    }
    
    memcpy(vet_merge, vet_base, tam_bytes);
    memcpy(vet_insert, vet_base, tam_bytes);
    
    *ptr_status_merge = m_sort_pedidos(vet_merge, c, tam);
    *ptr_status_insert = i_sort_pedidos(vet_insert, c, tam);

    free(vet_merge);
    free(vet_insert);
}

// TODO: implementar `void exibir_relatorio()` quando a função de imprimir pedido estiver pronta 
