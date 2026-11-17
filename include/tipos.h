#pragma once

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