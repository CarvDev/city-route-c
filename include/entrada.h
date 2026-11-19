#pragma once

/*
 * Função : limpar_buffer
 * Complexidade Temporal : O(n), onde n é o número de caracteres restantes na linha
 * Descarta os caracteres restantes do buffer de entrada até encontrar uma
 * quebra de linha ou o fim do arquivo (EOF).
 */
void limpar_buffer(void);

/*
 * Função : ler_string
 * Complexidade Temporal : O(n), onde n é o tamanho máximo da string lida
 * Lê uma linha da entrada padrão e a armazena em dest, removendo a quebra de
 * linha final. Se a entrada exceder tam, o restante da linha é descartado.
 * Em caso de falha de leitura, dest recebe uma string vazia.
 */
void ler_string(char *restrict dest, int tam);

/*
 * Função : ler_inteiro
 * Complexidade Temporal : O(n), onde n é o número de caracteres lidos na linha
 * Lê um inteiro da entrada padrão e limpa o buffer em seguida.
 * Retorna INT_MIN como código de erro caso a leitura falhe.
 */
int ler_inteiro(void);

/*
 * Função : pausar
 * Complexidade Temporal : O(n), onde n é o número de caracteres restantes na linha
 * Exibe uma mensagem opcional e aguarda o usuário pressionar ENTER.
 * Se `mensagem` for NULL, nenhuma mensagem é exibida.
 */
void pausar(const char *mensagem);
