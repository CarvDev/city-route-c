#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static int string_vazia(const char *s) {
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

int ler_inteiro(void) {
    int valor;
    if (scanf("%d", &valor) != 1) {
        valor = INT_MIN; // define INT_MIN como código de erro
    }

    /*
     Obs: para o estado atual do sistema essa função funciona, mas pode ser 
      necessário refatorá-la mais pra frente. 
      
     Problemas que ela possui: 
       * INT_MIN pode ser um valor de entrada válido, então não seria o código 
        de erro ideal 
       * scanf("%d") tem comportamento indefinido em overflow.
    */

    limpar_buffer();
    return valor;
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
