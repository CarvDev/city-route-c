#pragma once

#include <stddef.h>
#include "tipos.h"

/*
 * Função: historico_copiar.
 * Complexidade Temporal: O(n) no pior caso, onde n é a quantidade de pedidos.
 * Retorna vetor alocado com cópia dos pedidos ou NULL se alocação falhar. 
 * Grava quantidade em ptr_tam.
 * o chamador deve liberar o vetor com free().
 */
Pedido *historico_copiar(const Historico *hist, size_t *ptr_tam);
