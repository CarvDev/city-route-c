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
