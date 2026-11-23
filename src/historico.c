#include "historico.h"
#include "pedido.h"
#include "tipos.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

Pedido *historico_copiar(const Historico *hist, size_t *ptr_tam) {
    if (hist == NULL || hist->tamanho == 0 || ptr_tam == NULL || 
        mul_estoura_size(hist->tamanho, sizeof(Pedido))) return NULL;

    Pedido *vet_pedidos = malloc(hist->tamanho * sizeof(Pedido));
    if (vet_pedidos == NULL) return NULL;

    size_t tamanho = hist->tamanho;
    NoHistorico *aux = hist->inicio;

    size_t i = 0;
    for (; i < tamanho; i++) {
        if (aux == NULL) break; // A lista pode ser menor do que o valor informado
        vet_pedidos[i] = aux->pedido;
        aux = aux->prox;
    }
    *ptr_tam = i;

    return vet_pedidos;    
}


Historico *historico_inicializar(void) {
    Historico *hist = malloc(sizeof *hist);
    if (hist != NULL) *hist = (Historico){0};
    return hist;
}

int historico_registrar(Historico *hist, Pedido pedido) {
    if (hist == NULL || hist->tamanho == SIZE_MAX) return 0;

    NoHistorico *no = malloc(sizeof *no);
    if (no == NULL) return 0;

    *no = (NoHistorico){ .pedido = pedido, .prox = NULL };

    if (hist->fim == NULL) {
        hist->inicio = no;
    } else {
        hist->fim->prox = no;
    }

    hist->fim = no;
    hist->tamanho++;
    return 1;
}

void historico_listar(const Historico *hist) {
    if (hist == NULL || hist->inicio == NULL) return;

    imprimir_cabecalho_pedidos();
    for (const NoHistorico *no = hist->inicio; no != NULL; no = no->prox) {
        imprimir_pedido(&no->pedido);
    }
}

const Pedido *historico_buscar(const Historico *hist, int codigo) {
    if (hist == NULL) return NULL;

    for (const NoHistorico *no = hist->inicio; no != NULL; no = no->prox) {
        if (no->pedido.cod_rastreio == codigo) return &no->pedido;
    }

    return NULL;
}

void historico_liberar(Historico *hist) {
    if (hist == NULL) return;

    NoHistorico *no = hist->inicio;
    while (no != NULL) {
        NoHistorico *prox = no->prox;
        free(no);
        no = prox;
    }

    free(hist);
}
