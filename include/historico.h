#pragma once

#include <stddef.h>
#include "tipos.h"

/*
 * Função : historico_copiar
 * Complexidade Temporal : O(n), onde n é a quantidade de pedidos do histórico
 * Complexidade Espacial : O(n) para o vetor retornado
 * Copia os pedidos de `hist` para um vetor alocado dinamicamente e grava a
 * quantidade de elementos copiados em `ptr_tam`.
 * O chamador é responsável por liberar o vetor retornado com free().
 * Retorna NULL se a alocação falhar ou o histórico for vazio.
 */
Pedido *historico_copiar(const Historico *hist, size_t *ptr_tam);
