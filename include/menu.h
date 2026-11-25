#pragma once

#include "sistema.h"

#define LINHA_PADRAO "------------------------------------------"
#define PAUSA_PADRAO "Pressione ENTER para continuar..."

typedef void (*Acao)(struct Sistema *); // para passar o estado do sistema ao menu

typedef struct {
    const char *rotulo;
    Acao        acao; 
} ItemMenu;

/* 
 * Cada módulo definirá suas ações como funções pequenas.
 * O menu receberá como um vetor.
 * NULL sinalizará que ainda não foi implementado.
 * Ex:
    const ItemMenu ITENS_PONTOS[] = {
        { "Cadastrar ponto",            acao_cadastrar_ponto },
        { "Buscar ponto por codigo",    NULL }
        ...
    };
*/

/*
 * Função: exibir_prompt.
 * Complexidade Temporal: O(1) no pior caso.
 * Imprime o prompt padrão definido em menu.c descarrega o buffer
 * de saída, garantindo que ele seja exibido imediatamente.
 */
void exibir_prompt(void);

/*
 * Função: exibir_ajuda.
 * Complexidade Temporal: O(1) no pior caso, pois o manual é texto constante.
 * Exibe na saída padrão o manual de uso com opções, módulos, navegação e
 * regras de entrada. Não lê entradas nem altera o estado do sistema.
 */
void exibir_ajuda(void);

/*
 * Função: executar_menu.
 * Complexidade Temporal: O(n) por iteração do laço (exibicao dos n itens),
 * mais o custo da acao escolhida; o numero de iteracoes depende do usuario.
 * Mostra o título e os itens, lê a opçãoo e chama a ação escolhida.
 */
void executar_menu(const char *titulo, const ItemMenu *itens,
    size_t n, struct Sistema *s);

/*
 * Função: iniciar_menu.
 * Complexidade Temporal: O(1) no pior caso por ciclo de interação, 
 * sem contar operações invocadas.
 * Exibe o menu principal e direciona para os menus dos módulos do sistema.
 */
void iniciar_menu(struct Sistema *s);