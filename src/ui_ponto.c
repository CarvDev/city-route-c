#include "ui_ponto.h"
#include "menu.h"
#include "utils.h"


static const ItemMenu ITENS_PONTOS[] = {
    { "Cadastrar ponto",           NULL},
    { "Buscar ponto por código",   NULL },
    { "Listar pontos em ordem",    NULL },
    { "Excluir ponto",             NULL }
};

void menu_pontos_entrega(struct Sistema *s) {
    executar_menu("Módulo 1 - Pontos de Entrega", ITENS_PONTOS,
        NUM_ITENS(ITENS_PONTOS), s);
}