#pragma once

#include "tipos.h"

/*
 * Função: imprimir_pedido.
 * Complexidade Temporal: O(1) no pior caso.
 * Imprime em uma linha os campos de um pedido, seguindo o formato de
 * colunas definido por `imprimir_cabecalho_pedidos`.
 * Não imprime nada se `p` for NULL.
 */
void imprimir_pedido(const Pedido *p);

/*
 * Função: imprimir_cabecalho_pedidos.
 * Complexidade Temporal: O(1) no pior caso.
 * Imprime o cabeçalho das colunas utilizadas nas listagens de pedidos.
 */
void imprimir_cabecalho_pedidos(void);
