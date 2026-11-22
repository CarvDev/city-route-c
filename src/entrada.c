#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/*
  * Valida se a string não é vazia percorrendo
  * seus caracteres e verificando se pelo menos 
  * um deles não é um espaço em branco.
*/
static int string_vazia(const char *s) {
    if (s == NULL) return 1;

    for (; *s != '\0'; s++) {
        if (!isspace((unsigned char)*s)) return 0;
    }
    return 1;
}

void limpar_buffer(void) {
    int c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int ler_string(char *dest, size_t tam) {
    if (dest == NULL) return 0;

    // O tamanho da string precisa ser maior que 0
    // e caber em int, pois é o que fgets recebe
    if (tam <= 0 || tam > INT_MAX) return 0;

    if (!fgets(dest, (int)tam, stdin)) {
        // Erro na entrada (EOF, etc)
        dest[0] = '\0';
        return 0;
    }

    char *ptr = &dest[strcspn(dest, "\n")];
    if (*ptr == '\n') {
        *ptr = '\0';
    } else {
        limpar_buffer();   // entrada truncada: descarta o lixo no buffer
        dest[0] = '\0';
        return 0;
    }

    return !string_vazia(dest);
}

int ler_int(int *dest) {
    if (dest == NULL) return 0;

    char buf[64];
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0; // EOF ou erro de leitura
    }

    if (strchr(buf, '\n') == NULL && !feof(stdin)) {
        limpar_buffer();
        return 0; // Linha maior que o buffer
    }

    // Converte o número
    char *fim;
    errno = 0;
    long v = strtol(buf, &fim, 10);

    // Verifica se algum dígito foi lido 
    if (fim == buf) {
        return 0;
    }

    // Verifica limites do tipo int
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) {
        return 0;
    }

    *dest = (int)v;
    return 1;
}

int ler_double(double *dest) {
    if (scanf("%lf", dest) != 1) {
        limpar_buffer();
        return 0;
    }
    limpar_buffer();

    return isfinite(*dest);
}

void pausar(const char *mensagem) {
    if (mensagem != NULL) {
        printf("%s", mensagem);
        fflush(stdout);
    }

    int c = getchar();
    if (c != '\n' && c != EOF) limpar_buffer();
}
