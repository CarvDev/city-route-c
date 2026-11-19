#include "historico.h"
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
