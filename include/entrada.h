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
 * Função: ler_inteiro.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres lidos.
 * Lê um inteiro da entrada padrão e retorna INT_MIN em caso de falha.
 */
int ler_inteiro(void);

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
