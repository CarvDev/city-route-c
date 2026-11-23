#include "sistema.h"
#include "bst.h"
#include <stdlib.h>
#include "heap.h"
#include "historico.h"

#include <math.h>

int sistema_iniciar(Sistema *s) {
    if (s == NULL) return 0;

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = historico_inicializar();
    if (s->historico == NULL) return 0;

    return 1;
}

void sistema_encerrar(Sistema *s) {
    if (s == NULL) return;

    bst_liberar(s->pontos);
    free(s->fila.dados);
    historico_liberar(s->historico);

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = NULL;
}

int sistema_despachar(Sistema *s, Pedido *saida) {
    if (s == NULL) return 0;

    const Pedido *proximo = heap_proximo(&s->fila);
    if (proximo == NULL) return 0;

    // Se o registro falhar, o pedido continua na fila.
    if (!historico_registrar(s->historico, *proximo)) return 0;

    return heap_extrair(&s->fila, saida);
}

int sistema_excluir_ponto(Sistema *s, int id) {
    if (s == NULL) return 0;

    for (size_t i = 0; i < s->fila.tamanho; i++) {
        if (s->fila.dados[i].id_destino == id) return 0;
    }

    int ok = 0;
    s->pontos = bst_remover(s->pontos, id, &ok);
    return ok;
}

int sistema_inserir_pedido(Sistema *s, Pedido pedido) {
    if (s == NULL || pedido.prioridade < 1 || pedido.prioridade > 3 ||
        !isfinite(pedido.peso) || pedido.peso <= 0 ||
        !isfinite(pedido.valor) || pedido.valor < 0 ||
        bst_buscar(s->pontos, pedido.id_destino) == NULL ||
        historico_buscar(s->historico, pedido.cod_rastreio) != NULL) {
        return 0;
    }

    for (size_t i = 0; i < s->fila.tamanho; i++) {
        if (s->fila.dados[i].cod_rastreio == pedido.cod_rastreio) return 0;
    }

    return heap_inserir(&s->fila, pedido);
}
