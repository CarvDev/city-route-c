#include "ui_historico.h"
#include "menu.h"
#include "utils.h"


static const ItemMenu ITENS_HISTORICO[] = {
    { "Consultar histórico completo",              NULL },
    { "Buscar pedido por código de rastreio",      NULL }
};

void menu_historico(struct Sistema *s) {
    executar_menu("Módulo 3 - Histórico", ITENS_HISTORICO,
        NUM_ITENS(ITENS_HISTORICO), s);
}
