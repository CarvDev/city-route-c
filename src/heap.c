#include "heap.h"
#include "utils.h"

#include <limits.h>
#include <stdlib.h>

static int vem_antes(const Pedido *a, const Pedido *b) {
    if (a->prioridade != b->prioridade) return a->prioridade < b->prioridade;
    return a->ordem_chegada < b->ordem_chegada;
}

static int ampliar_heap(HeapPedidos *heap) {
    size_t capacidade = heap->capacidade;
    if (capacidade > SIZE_MAX / 2) return 0;

    capacidade = capacidade == 0 ? 8 : capacidade * 2;
    if (mul_estoura_size(capacidade, sizeof *heap->dados)) return 0;

    Pedido *dados = realloc(heap->dados, capacidade * sizeof *dados);
    if (dados == NULL) return 0;

    heap->dados = dados;
    heap->capacidade = capacidade;
    return 1;
}

int heap_inserir(HeapPedidos *heap, Pedido pedido) {
    if (heap == NULL || heap->proxima_ordem == ULONG_MAX) return 0;
    if (heap->tamanho == heap->capacidade && !ampliar_heap(heap)) return 0;

    pedido.ordem_chegada = heap->proxima_ordem++;
    size_t indice = heap->tamanho++;

    while (indice > 0) {
        size_t pai = (indice - 1) / 2;
        if (!vem_antes(&pedido, &heap->dados[pai])) break;
        heap->dados[indice] = heap->dados[pai];
        indice = pai;
    }

    heap->dados[indice] = pedido;
    return 1;
}

const Pedido *heap_proximo(const HeapPedidos *heap) {
    if (heap == NULL || heap->tamanho == 0) return NULL;
    return &heap->dados[0];
}

int heap_extrair(HeapPedidos *heap, Pedido *saida) {
    const Pedido *proximo = heap_proximo(heap);
    if (proximo == NULL) return 0;
    if (saida != NULL) *saida = *proximo;

    heap->tamanho--;
    if (heap->tamanho == 0) return 1;

    Pedido ultimo = heap->dados[heap->tamanho];
    size_t indice = 0;

    while (indice < heap->tamanho / 2) {
        size_t filho = 2 * indice + 1;
        size_t direito = filho + 1;

        if (direito < heap->tamanho &&
            vem_antes(&heap->dados[direito], &heap->dados[filho])) {
            filho = direito;
        }

        if (!vem_antes(&heap->dados[filho], &ultimo)) break;
        heap->dados[indice] = heap->dados[filho];
        indice = filho;
    }

    heap->dados[indice] = ultimo;
    return 1;
}