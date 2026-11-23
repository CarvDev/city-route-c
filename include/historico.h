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

/*
 * Função: historico_inicializar.
 * Complexidade Temporal: O(1) no pior caso.
 * Cria um histórico vazio ou retorna NULL se a alocação falhar.
 */
Historico *historico_inicializar(void);

/*
 * Função: historico_registrar.
 * Complexidade Temporal: O(1) no pior caso.
 * Copia o pedido para o final da lista. Retorna 1 em caso de sucesso
 * ou 0 em caso de falha, preservando a lista.
 */
int historico_registrar(Historico *hist, Pedido pedido);

/*
 * Função: historico_listar.
 * Complexidade Temporal: O(n) no pior caso, para n despachos.
 * Exibe os pedidos na ordem em que foram despachados.
 */
void historico_listar(const Historico *hist);

/*
 * Função: historico_buscar.
 * Complexidade Temporal: O(n) no pior caso, para n despachos.
 * Retorna o pedido com o código informado ou NULL se não o encontrar.
 * O ponteiro retornado pertence ao histórico.
 */
const Pedido *historico_buscar(const Historico *hist, int codigo);

/*
 * Função: historico_liberar.
 * Complexidade Temporal: O(n) no pior caso, para n despachos.
 * Libera os nós e a estrutura de controle. Aceita NULL.
 */
void historico_liberar(Historico *hist);