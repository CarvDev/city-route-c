#pragma once 

#include "tipos.h"

/*
 * Função: heap_inserir.
 * Complexidade Temporal: O(n) no pior caso, quando o vetor é realocado.
 * Sem realocação, custa O(log n). Insere por prioridade, com desempate
 * por ordem de chegada. Retorna 1 em caso de sucesso ou 0 se falhar.
 */
int heap_inserir(HeapPedidos *heap, Pedido pedido);

/*
 * Função: heap_proximo.
 * Complexidade Temporal: O(1) no pior caso.
 * Retorna a raiz sem removê-la, ou NULL se a fila estiver vazia.
 * O ponteiro pertence ao heap e deve ser usado antes de alterá-lo.
 */
const Pedido *heap_proximo(const HeapPedidos *heap);

/*
 * Função: heap_extrair.
 * Complexidade Temporal: O(log n) no pior caso.
 * Remove a raiz e a copia para saida, se informada. Retorna 1 em caso
 * de sucesso ou 0 se o heap estiver vazio ou for NULL.
 */
int heap_extrair(HeapPedidos *heap, Pedido *saida);