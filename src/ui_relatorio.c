#include "ui_relatorio.h"
#include "entrada.h"
#include "historico.h"
#include "menu.h"
#include "ordenacao.h"
#include "relatorio.h"
#include "tipos.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

static void exibir_resultado_comparacao(Criterio c, const EstatisticasOrdenacao *ptr_status_insert, 
    const EstatisticasOrdenacao *ptr_status_merge) 
{
    if (ptr_status_insert == NULL) {
        fprintf(stderr, "[ERRO] %s: estatísticas do Insertion Sort inválidas.\n", __func__);
        return;
    }
    if (ptr_status_merge == NULL) {
        fprintf(stderr, "[ERRO] %s: estatísticas do Merge Sort inválidas.\n", __func__);
        return;
    }

    const char *vet_criterios[] = {
        [POR_VALOR] = "Por Valor",
        [POR_RASTREIO] = "Por Rastreio"
    };
    size_t num_criteiros = sizeof(vet_criterios) / sizeof(char*);
    const char *criterio = ((size_t)c < num_criteiros)? vet_criterios[c] : "Desconhecido";

    puts(LINHA_PADRAO);
    printf("          Critério: %s\n", criterio);
    imprimir_estatisticas(ptr_status_insert, "Insertion Sort");
    imprimir_estatisticas(ptr_status_merge, "Merge Sort");
}

static int solicitar_criterio(Criterio *c) {
    puts(LINHA_PADRAO);
    printf("Critério a ser utilizado:\n");
    printf("1 - Por Código de Rastreio\n");
    printf("2 - Por Valor\n");
    exibir_prompt();

    switch (ler_inteiro()) {
        case 1: *c = POR_RASTREIO; return 1;
        case 2: *c = POR_VALOR;    return 1;
        default:                   return 0;
    }
}

static void acao_comparar_algoritmos(struct Sistema *s) {
    if(s->historico->tamanho == 0 || s->historico->inicio == NULL) {
        fprintf(stderr, "[AVISO] Histórico vazio. ");
        pausar("Pressione ENTER para continuar...");
        return;
    }

    Criterio c;
    EstatisticasOrdenacao status_insert = {0};
    EstatisticasOrdenacao status_merge = {0};
    if (!solicitar_criterio(&c)) {
        fprintf(stderr, "[AVISO] Critério inválido. ");
        pausar("Pressione ENTER para continuar...");
        return;
    }

    size_t tam;
    Pedido *vet_pedidos = historico_copiar(s->historico, &tam);
    if (vet_pedidos == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memória para cópia de histórico\n");
        return;
    }

    comparar_ordenacoes(vet_pedidos, tam, c, &status_insert, &status_merge);
    exibir_resultado_comparacao(c,&status_insert, &status_merge);
    free(vet_pedidos);
}

static const ItemMenu ITENS_RELATORIOS[] = {
    { "Relatório ordenado",                NULL },
    { "Comparar algoritmos de ordenação",  acao_comparar_algoritmos},
    { "Carga inicial automatizada",        NULL }
};

void menu_relatorios(struct Sistema *s) {
    executar_menu("Módulo 4 - Relatórios", ITENS_RELATORIOS,
        NUM_ITENS(ITENS_RELATORIOS), s);
}
