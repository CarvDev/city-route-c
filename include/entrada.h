#pragma once

/*
 * Função: limpar_buffer.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres restantes na linha.
 * Descarta os caracteres restantes do buffer de entrada até '\n' ou EOF.
 */
void limpar_buffer(void);

/*
 * Função: ler_string.
 * Complexidade Temporal: O(n) no pior caso, onde n é o tamanho máximo lido.
 * Lê uma linha em dest (remove '\n'); em falha, dest recebe string vazia.
 */
void ler_string(char *restrict dest, int tam);

/*
 * Função: ler_inteiro.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres lidos.
 * Lê um inteiro da entrada padrão e retorna INT_MIN em caso de falha.
 */
int ler_inteiro(void);

/*
 * Função: pausar.
 * Complexidade Temporal: O(n) no pior caso, onde n é o número de caracteres restantes na linha.
 * Exibe mensagem opcional e aguarda ENTER; não exibe nada se mensagem for NULL.
 */
void pausar(const char *mensagem);
