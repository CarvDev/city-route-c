#include "ui_pedido.h"
#include "entrada.h"
#include "heap.h"
#include "menu.h"
#include "pedido.h"
#include "utils.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

static int ler_dados_pedido(Pedido *pedido) {
    printf("Código de rastreio: ");
    if (!ler_int(&pedido->cod_rastreio)) return 0;

    printf("Prioridade (1 - Expressa, 2 - VIP, 3 - Convencional): ");
    if (!ler_int(&pedido->prioridade) ||
        pedido->prioridade < 1 || pedido->prioridade > 3) {
        return 0;
    }

    printf("ID do destino: ");
    if (!ler_int(&pedido->id_destino)) return 0;

    double peso;
    printf("Peso (kg): ");
    if (!ler_double(&peso) || !isfinite(peso) ||
        peso <= 0 || peso > FLT_MAX) {
        return 0;
    }

    pedido->peso = (float)peso;
    if (pedido->peso <= 0) return 0;

    double valor;
    printf("Valor (R$): ");
    if (!ler_double(&valor) || !isfinite(valor) ||
        valor < 0 || valor > FLT_MAX) {
        return 0;
    }

    pedido->valor = (float)valor;
    return 1;
}

static void acao_inserir_pedido(struct Sistema *s) {
    Pedido pedido = {0};

    if (!ler_dados_pedido(&pedido)) {
        fprintf(stderr, "[AVISO] Dados do pedido inválidos. ");
    } else if (!sistema_inserir_pedido(s, pedido)) {
        fprintf(stderr, "[ERRO] Falha ao inserir. Verifique o destino e o rastreio. ");
    } else {
        puts("[OK] Pedido inserido com sucesso.");
    }

    pausar(PAUSA_PADRAO);
}

static void acao_consultar_proximo(struct Sistema *s) {
    const Pedido *pedido = heap_proximo(&s->fila);

    if (pedido == NULL) {
        fprintf(stderr, "[AVISO] Nenhum pedido pendente. ");
    } else {
        imprimir_cabecalho_pedidos();
        imprimir_pedido(pedido);
    }

    pausar(PAUSA_PADRAO);
}

static void acao_despachar_pedido(struct Sistema *s) {
    Pedido pedido;

    if (heap_proximo(&s->fila) == NULL) {
        fprintf(stderr, "[AVISO] Nenhum pedido pendente. ");
    } else if (!sistema_despachar(s, &pedido)) {
        fprintf(stderr, "[ERRO] Falha ao registrar. O pedido continua pendente. ");
    } else {
        printf("[OK] Pedido %d despachado e registrado no histórico.\n",
            pedido.cod_rastreio);
    }

    pausar(PAUSA_PADRAO);
}

static void acao_listar_pendentes(struct Sistema *s) {
    if (s->fila.tamanho == 0) {
        fprintf(stderr, "[AVISO] Nenhum pedido pendente. ");
    } else {
        imprimir_cabecalho_pedidos();
        for (size_t i = 0; i < s->fila.tamanho; i++) {
            imprimir_pedido(&s->fila.dados[i]);
        }
    }

    pausar(PAUSA_PADRAO);
}

static const ItemMenu ITENS_PEDIDOS[] = {
    { "Inserir pedido",           acao_inserir_pedido },
    { "Consultar próximo pedido", acao_consultar_proximo },
    { "Processar despacho",       acao_despachar_pedido },
    { "Exibir pedidos pendentes", acao_listar_pendentes }
};

void menu_pedidos(struct Sistema *s) {
    executar_menu("Módulo 2 - Pedidos", ITENS_PEDIDOS,
        NUM_ITENS(ITENS_PEDIDOS), s);
}