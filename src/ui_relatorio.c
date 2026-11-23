#include "ui_relatorio.h"
#include "entrada.h"
#include "historico.h"
#include "menu.h"
#include "ordenacao.h"
#include "pedido.h"
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

    int c_lido;
    if (!ler_int(&c_lido)) return 0;
    switch (c_lido) {
        case 1: *c = POR_RASTREIO; return 1;
        case 2: *c = POR_VALOR;    return 1;
        default:                   return 0;
    }
}

static void acao_comparar_algoritmos(struct Sistema *s) {
    if(s->historico->tamanho == 0 || s->historico->inicio == NULL) {
        fprintf(stderr, "[AVISO] Histórico vazio. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    Criterio c;
    EstatisticasOrdenacao status_insert = {0};
    EstatisticasOrdenacao status_merge = {0};
    if (!solicitar_criterio(&c)) {
        fprintf(stderr, "[AVISO] Critério inválido. ");
        pausar(PAUSA_PADRAO);
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

static void acao_relatorio_ordenado(struct Sistema *s) {
    if (s->historico->tamanho == 0 || s->historico->inicio == NULL) {
        fprintf(stderr, "[AVISO] Histórico vazio. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    Criterio c;
    if (!solicitar_criterio(&c)) {
        fprintf(stderr, "[AVISO] Critério inválido. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    size_t tam = 0;
    Pedido *vet_pedidos = gerar_relatorio_ordenado(s->historico, c, &tam);
    if (vet_pedidos == NULL) {
        fprintf(stderr, "[ERRO] Falha ao gerar relatório ordenado\n");
        pausar(PAUSA_PADRAO);
        return;
    }

    puts(LINHA_PADRAO);
    imprimir_cabecalho_pedidos();
    for (size_t i = 0; i < tam; i++) {
        imprimir_pedido(&vet_pedidos[i]);
    }
    puts(LINHA_PADRAO);
    free(vet_pedidos);
    pausar(PAUSA_PADRAO);
}

static int sistema_tem_dados(const struct Sistema *s) {
    if (s->pontos != NULL) return 1;
    if (s->fila.tamanho > 0) return 1;
    if (s->historico != NULL && s->historico->tamanho > 0) return 1;
    return 0;
}

static int confirmar_substituicao(void) {
    char resposta[8];

    fprintf(stderr, "[AVISO] A carga apagará todos os dados atuais. ");
    printf("Confirmar? (S/N): ");
    if (!ler_string(resposta, sizeof resposta)) return 0;

    return resposta[0] == 's' || resposta[0] == 'S';
}

static int solicitar_quantidade_carga(size_t *qtd) {
    puts(LINHA_PADRAO);
    printf("Quantidade de pontos e pedidos:\n");
    printf("1 - 100\n");
    printf("2 - 1.000\n");
    printf("3 - 10.000\n");
    exibir_prompt();

    int opcao;
    if (!ler_int(&opcao)) return 0;

    switch (opcao) {
        case 1: *qtd = 100;   return 1;
        case 2: *qtd = 1000;  return 1;
        case 3: *qtd = 10000; return 1;
        default:              return 0;
    }
}

static void acao_carga_teste(struct Sistema *s) {
    if (sistema_tem_dados(s) && !confirmar_substituicao()) {
        fprintf(stderr, "[AVISO] Operação cancelada. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    size_t qtd;
    if (!solicitar_quantidade_carga(&qtd)) {
        fprintf(stderr, "[AVISO] Quantidade inválida. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    if (!sistema_carga_teste(s, qtd, qtd)) {
        fprintf(stderr, "[ERRO] Falha ao gerar a carga inicial. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    puts(LINHA_PADRAO);
    printf("[OK] Carga gerada: %zu pontos, %zu pedidos pendentes e "
        "%zu despachados.\n", qtd, s->fila.tamanho, s->historico->tamanho);
    puts(LINHA_PADRAO);
    pausar(PAUSA_PADRAO);
}

static const ItemMenu ITENS_RELATORIOS[] = {
    { "Relatório ordenado",                acao_relatorio_ordenado },
    { "Comparar algoritmos de ordenação",  acao_comparar_algoritmos},
    { "Carga inicial automatizada",        acao_carga_teste }
};

void menu_relatorios(struct Sistema *s) {
    executar_menu("Módulo 4 - Relatórios", ITENS_RELATORIOS,
        NUM_ITENS(ITENS_RELATORIOS), s);
}
