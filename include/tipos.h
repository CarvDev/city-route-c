#pragma once

#include <stddef.h>

typedef struct {
    int id_ponto;
    char nome_local[100];
    double latitude;
    double longitude;
} PontoEntrega;

typedef struct NoBST {
    PontoEntrega ponto;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

typedef struct {
    int cod_rastreio;
    int prioridade; // 1, 2 ou 3
    unsigned long ordem_chegada; 
    float peso;
    int id_destino;
    float valor;
} Pedido;

typedef struct NoHistorico {
    Pedido pedido;
    struct NoHistorico *prox;
} NoHistorico;

typedef struct {
    NoHistorico *inicio;
    NoHistorico *fim;
    size_t tamanho;
} Historico;

typedef enum {
    POR_RASTREIO,
    POR_VALOR
} Criterio;

typedef struct {
    unsigned long comparacoes;
    unsigned long movimentacoes;
    double segundos;
} EstatisticasOrdenacao;

typedef struct {
    Pedido *dados;
    size_t tamanho;
    size_t capacidade;
    unsigned long proxima_ordem;
} HeapPedidos;
