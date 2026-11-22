#include "sistema.h"
#include "bst.h"
#include <stdlib.h>

int sistema_iniciar(Sistema *s) {
    if (s == NULL) return 0;

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = calloc(1, sizeof *s->historico);

    if (s->historico == NULL) return 0;

    return 1;
}

void sistema_encerrar(Sistema *s) {
    if (s == NULL) return;

    bst_liberar(s->pontos);
    free(s->fila.dados);
    free(s->historico);

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = NULL;
}
