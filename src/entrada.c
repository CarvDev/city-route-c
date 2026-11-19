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

void pausar(const char *mensagem) {
    if (mensagem != NULL) {
        printf("%s", mensagem);
        fflush(stdout);
    }

    int c = getchar();
    if (c != '\n' && c != EOF) limpar_buffer();
}
