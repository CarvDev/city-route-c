#include "ui_ponto.h"
#include "bst.h"
#include "entrada.h"
#include "menu.h"
#include "utils.h"

#include <stdio.h>

static void exibir_ponto(const PontoEntrega *p) {
    printf("ID: %d | Nome: %s | Latitude: %.6f | Longitude: %.6f\n",
        p->id_ponto, p->nome_local, p->latitude, p->longitude);
}

static void acao_cadastrar_ponto(struct Sistema *s) {
    PontoEntrega p = {0};

    printf("ID do ponto: ");
    if (!ler_int(&p.id_ponto)) {
        fprintf(stderr, "[AVISO] ID inválido. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    if (bst_buscar(s->pontos, p.id_ponto) != NULL) {
        fprintf(stderr, "[AVISO] Já existe um ponto com esse ID. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    printf("Nome do local: ");
    if (!ler_string(p.nome_local, sizeof(p.nome_local))) {
        fprintf(stderr, "[AVISO] Nome inválido. ");
        fprintf(stderr, "O nome deve ter menos de 100 caracteres ");
        fprintf(stderr, "e não deve ser vazio. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    printf("Latitude: ");
    if (!ler_double(&p.latitude)) {
        fprintf(stderr, "[AVISO] Latitude inválida. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    printf("Longitude: ");
    if (!ler_double(&p.longitude)) {
        fprintf(stderr, "[AVISO] Longitude inválida. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    int ok = 0;
    s->pontos = bst_inserir(s->pontos, p, &ok);

    if (!ok) {
        fprintf(stderr, "[ERRO] Falha ao alocar memória para o ponto.\n");
        pausar(PAUSA_PADRAO);
        return;
    }

    printf("[OK] Ponto cadastrado com sucesso.\n");
    pausar(PAUSA_PADRAO);
}

static void acao_buscar_ponto(struct Sistema *s) {
    int id;

    printf("ID do ponto: ");
    if (!ler_int(&id)) {
        fprintf(stderr, "[AVISO] ID inválido. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    const NoBST *no = bst_buscar(s->pontos, id);
    if (no == NULL) {
        fprintf(stderr, "[AVISO] Ponto não encontrado. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    puts(LINHA_PADRAO);
    exibir_ponto(&no->ponto);
    puts(LINHA_PADRAO);
    pausar(PAUSA_PADRAO);
}

static void acao_listar_pontos(struct Sistema *s) {
    if (s->pontos == NULL) {
        fprintf(stderr, "[AVISO] Nenhum ponto cadastrado. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    puts(LINHA_PADRAO);
    bst_listar_em_ordem(s->pontos);
    puts(LINHA_PADRAO);
    pausar(PAUSA_PADRAO);
}

static void acao_excluir_ponto(struct Sistema *s) {
    int id;

    printf("ID do ponto: ");
    if (!ler_int(&id)) {
        fprintf(stderr, "[AVISO] ID inválido. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    if (!sistema_excluir_ponto(s, id)) {
        fprintf(stderr, "[AVISO] Ponto inexistente ou com pedidos pendentes. ");
        pausar(PAUSA_PADRAO);
        return;
    }

    printf("[OK] Ponto removido com sucesso.\n");
    pausar(PAUSA_PADRAO);
}

static const ItemMenu ITENS_PONTOS[] = {
    { "Cadastrar ponto",         acao_cadastrar_ponto },
    { "Buscar ponto por código", acao_buscar_ponto },
    { "Listar pontos em ordem",   acao_listar_pontos },
    { "Excluir ponto",            acao_excluir_ponto }
};

void menu_pontos_entrega(struct Sistema *s) {
    executar_menu("Módulo 1 - Pontos de Entrega", ITENS_PONTOS,
        NUM_ITENS(ITENS_PONTOS), s);
}
