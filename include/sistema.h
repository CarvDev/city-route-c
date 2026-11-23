#pragma once

#include "tipos.h"

// para guardar o estado, inicializado na main 
typedef struct Sistema {
    NoBST       *pontos;
    HeapPedidos  fila;
    Historico   *historico;
} Sistema;

/*
 * Função: sistema_iniciar.
 * Complexidade Temporal: O(1) no pior caso.
 * Implementação atual: inicializa o estado do sistema com todos 
 * os campos zerados, alocando os campos dinamicamente. 
 * Retorna 0 se `s` for NULL ou se a alocação falhar.
 
 * Implementação futura: Chamar os métodos propriamente definidos
 * nos módulos para incialização das estruturas de dados do sistema. 
 */
int sistema_iniciar(Sistema *s);

/*
 * Função: sistema_encerrar.
 * Complexidade Temporal: O(1) no pior caso.
 * Libera a memória alocada pelo sistema e zera seus campos. Segura quando
 * `s` for NULL.
 */
void sistema_encerrar(Sistema *s);

/*
 * Função: sistema_inserir_pedido.
 * Complexidade Temporal: O(p + n + h) no pior caso, para p pontos,
 * n pedidos pendentes e h despachos.
 * Valida os dados, o destino e a unicidade do rastreio antes de inserir.
 * Retorna 1 em caso de sucesso ou 0 em caso de falha.
 */
int sistema_inserir_pedido(Sistema *s, Pedido pedido);

/*
 * Função: sistema_despachar.
 * Complexidade Temporal: O(log n) no pior caso, para n pedidos pendentes.
 * Registra o próximo pedido e o remove da fila. Copia o pedido para saida,
 * se informada. Retorna 1 em caso de sucesso ou 0 se não puder despachar.
 * Em caso de falha de alocação, o pedido permanece pendente.
 */
int sistema_despachar(Sistema *s, Pedido *saida);

/*
 * Função: sistema_excluir_ponto.
 * Complexidade Temporal: O(n + p) no pior caso, para n pedidos pendentes
 * e p pontos. Retorna 1 se remover o ponto, ou 0 se ele não existir
 * ou estiver vinculado a um pedido pendente.
 */
int sistema_excluir_ponto(Sistema *s, int id);