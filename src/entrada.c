#include <limits.h>
#include <stdio.h>
#include <string.h>

void limpar_buffer(void) {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

void ler_string(char *dest, int tam) {
    if (tam <= 0) return;

    if (!fgets(dest, (int)tam, stdin)) {
        dest[0] = '\0';
        return;
    }

    char *ptr = &dest[strcspn(dest, "\n")];
    if (*ptr == '\n') {
        *ptr = '\0';
    } else {
        limpar_buffer();   // entrada truncada: descarta o resto da linha
    }
}

int ler_inteiro(void) {
    int valor;
    if (scanf("%d", &valor) != 1) {
        valor = INT_MIN; // define INT_MIN como código de erro
    }

    limpar_buffer();
    return valor;
}

void pausar(char *mensagem) {
    if (mensagem != NULL) {
        printf("%s", mensagem);
        fflush(stdout);
    }

    int c = getchar();
    if (c != '\n' && c != EOF) limpar_buffer();
}
