#ifndef TIPOS_H
#define TIPOS_H

#include <stddef.h>

typedef struct {
    int id_ponto;         /* chave unica */
    char nome_local[100]; /* bairro ou localidade */
    double latitude;      /* coordenada geografica */
    double longitude;     /* coordenada geografica */
} PontoEntrega;

typedef struct NoBST {
    PontoEntrega ponto;   /* dado do no */
    struct NoBST *esq;    /* filho de chave menor */
    struct NoBST *dir;    /* filho de chave maior */
} NoBST;

typedef struct {
    int cod_rastreio;
    int prioridade; /* 1, 2 ou 3 */
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

#endif /* TIPOS_H */
