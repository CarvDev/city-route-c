#include "ui_historico.h"
#include "entrada.h"
#include "historico.h"
#include "menu.h"
#include "pedido.h"
#include "utils.h"

#include <stdio.h>

static void acao_listar_historico(struct Sistema *s) {
    if (s->historico->tamanho == 0) {
        fprintf(stderr, "[AVISO] Nenhum pedido despachado. ");
    } else {
        puts(LINHA_PADRAO);
        historico_listar(s->historico);
        puts(LINHA_PADRAO);
    }

    pausar(PAUSA_PADRAO);
}

static void acao_buscar_historico(struct Sistema *s) {
    int codigo;

    printf("Código de rastreio: ");
    if (!ler_int(&codigo)) {
        fprintf(stderr, "[AVISO] Código de rastreio inválido. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    const Pedido *pedido = historico_buscar(s->historico, codigo);

    if (pedido == NULL) {
        fprintf(stderr, "[AVISO] Pedido não encontrado no histórico. ");
    } else {
        puts(LINHA_PADRAO);
        imprimir_cabecalho_pedidos();
        imprimir_pedido(pedido);
        puts(LINHA_PADRAO);
    }

    pausar(PAUSA_PADRAO);
}

static const ItemMenu ITENS_HISTORICO[] = {
    { "Consultar histórico completo",        acao_listar_historico },
    { "Buscar pedido por código de rastreio", acao_buscar_historico }
};

void menu_historico(struct Sistema *s) {
    executar_menu("Módulo 3 - Histórico", ITENS_HISTORICO,
        NUM_ITENS(ITENS_HISTORICO), s);
}