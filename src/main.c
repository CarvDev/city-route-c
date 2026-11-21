#include "menu.h"
#include "sistema.h"

int main(void) {
    Sistema s;
    if (!sistema_iniciar(&s)) return 1;
    iniciar_menu(&s);
    sistema_encerrar(&s);
    return 0;
}