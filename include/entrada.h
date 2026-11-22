#pragma once

#include <stddef.h>

/*
 * Função: limpar_buffer.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres restantes na linha.
 * Descarta os caracteres restantes do buffer de entrada até '\n' ou EOF.
 */
void limpar_buffer(void);

/*
 * Função: ler_string.
 * Complexidade Temporal: O(n) no pior caso, onde n é o tamanho máximo lido.
 * Lê uma linha em dest (remove '\n') e retorna 1 em caso de sucesso.
 * Retorna 0 se não for possível ler, se a entrada for truncada ou se a
 * string resultante for vazia; nesses casos, dest[0] receberá '\0'.
 */
int ler_string(char *restrict dest, size_t tam);

/*
 * Função: ler_int.
 * Complexidade Temporal: O(n) no pior caso, onde n é o tamanho da linha lida.
 * Lê uma linha da entrada padrão e converte o conteúdo para int, gravando-o
 * em dest. Retorna 1 em caso de sucesso e 0 se dest for NULL, houver erro/EOF,
 * a entrada for inválida (sem dígitos ou linha maior que o buffer) ou o valor 
 * estiver fora do intervalo de int.
 
 * Estratégia contra overflow: scanf("%d") possui comportamento indefinido para 
 * overflow de inteiros, por isso a leitura nessa função é feita com fgets em 
 * um buffer de tamanho fixo (64 bytes), enquanto a conversão usa strtol, que 
 * retorna um long int. Após a conversão, o valor é comparado com INT_MIN e 
 * INT_MAX antes do cast e somente após todas as validações passarem o cast é 
 * executado, garantindo que a conversão seja sempre segura.
 */
int ler_int(int *dest);

/*
 * Função: ler_double.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres lidos.
 * Lê um double da entrada padrão e grava em dest.
 * Retorna 1 em caso de sucesso e 0 se a entrada for inválida ou não finita
 * (NaN ou infinito).
 */
int ler_double(double *dest);

/*
 * Função: pausar.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres restantes na linha.
 * Exibe mensagem opcional e aguarda ENTER; não exibe nada se mensagem for NULL.
 */
void pausar(const char *mensagem);
