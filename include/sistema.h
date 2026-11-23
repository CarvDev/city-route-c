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

/*
 * Função: sistema_carga_teste.
 * Complexidade Temporal: O(p² + n²) no pior caso, para p pontos e
 * n = 2 * qtd_pedidos pedidos gerados. Cada inserção na BST pode custar
 * O(p) (árvore degenerada) e cada inserção de pedido valida unicidade em
 * O(n) pela RF04. O espaço auxiliar é O(p + n).
 * Descarta o estado atual (reset) e repovoa a BST, o heap e o histórico:
 * gera `qtd_pontos` pontos e `qtd_pedidos * 2` pedidos, despachando um a
 * cada duas inserções (RF06). Usa aleatoriedade (Fisher-Yates e sorteios),
 * de modo que a carga não é determinística. A prioridade é sorteada de
 * forma ponderada: 10% Expressa, 30% VIP e 60% Convencional.
 * Retorna 1 em caso de sucesso ou 0 se os argumentos forem inválidos ou
 * houver falha de alocação.
 */
int sistema_carga_teste(Sistema *s, size_t qtd_pontos, size_t qtd_pedidos);
