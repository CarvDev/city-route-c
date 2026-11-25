#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "sistema.h"

int main(int argc, char **argv) {
    if (argc == 2 && argv[1] != NULL &&
        (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        exibir_ajuda();
        return 0;
    }

    if (argc != 1) {
        if (argc == 2 && argv[1] != NULL) {
            fprintf(stderr, "[ERRO] Opção desconhecida: %s\n", argv[1]);
        } else {
            fprintf(stderr, "[ERRO] Número de argumentos inválido.\n");
        }
        fprintf(stderr, "Uso: %s [--help]\n", argv[0]);
        return 1;
    }

    Sistema s;
    if (!sistema_iniciar(&s)) return 1;
    iniciar_menu(&s);
    sistema_encerrar(&s);
    return 0;
}
