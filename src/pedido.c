#include "pedido.h"

#include <stdio.h>

void imprimir_pedido(const Pedido *p) {
    if (p == NULL) return;

    printf("%8d | %10d | %10lu | %10.2f | %8d | %12.2f\n",
        p->cod_rastreio,
        p->prioridade,
        p->ordem_chegada,
        p->peso,
        p->id_destino,
        p->valor);
}

void imprimir_cabecalho_pedidos(void) {
    printf("%-8s | %-10s | %-10s | %-10s | %-8s | %-12s\n",
        "Rastreio", "Prioridade", "Chegada", "Peso (kg)", "Destino", "Valor (R$)");
}
