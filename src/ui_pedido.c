#include "ui_pedido.h"
#include "menu.h"
#include "utils.h"


static const ItemMenu ITENS_PEDIDOS[] = {
    { "Inserir pedido",                NULL },
    { "Consultar próximo pedido",      NULL },
    { "Processar despacho",            NULL },
    { "Exibir pedidos pendentes",      NULL }
};

void menu_pedidos(struct Sistema *s) {
    executar_menu("Módulo 2 - Pedidos", ITENS_PEDIDOS,
        NUM_ITENS(ITENS_PEDIDOS), s);
}
