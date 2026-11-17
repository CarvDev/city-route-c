#include <stddef.h>
#include <stdio.h>
#include "entrada.h" // TROCAR PARA .H

#include "menu.h"

typedef void (*FuncaoMenu)(void);
static const char *PROMPT = "> ";

// Exibe o cabeçalho do sistema seguido do título da tela atual.
static void exibir_cabecalho(const char *titulo) {
    printf("\n");
    printf("==========================================\n");
    printf("              CITYROUTE C\n");
    printf("   Logística Urbana e Gestão de Pedidos\n");
    printf("==========================================\n");
    printf("%s\n", titulo);
    printf("------------------------------------------\n");
}

// Imprime o prompt definido globalmente
static void exibir_prompt(void) {
    printf("%s", PROMPT);
    fflush(stdout);
}


// Informa que a funcionalidade escolhida ainda será implementada.
static void exibir_placeholder(void) {
    printf("[AVISO] Esta funcionalidade do módulo será implementada em breve. ");
    pausar("Pressione ENTER para continuar... ");
}

// Template temporário de menu.
static void exibir_menu_temp(char *titulo, char **matriz_opcoes, int num_opcoes) {
    int opcao;

    do {
        exibir_cabecalho(titulo);
        for (int i = 0; i < num_opcoes; i++) {
            puts(matriz_opcoes[i]);
        }
        printf("0 - Voltar ao menu principal\n");
        printf("------------------------------------------\n");

        exibir_prompt();
        opcao = ler_inteiro();
        if (opcao == 0) return;
        if (opcao > 0 && opcao <= num_opcoes) {
            exibir_placeholder();
            continue;
        } 

        fprintf(stderr, "[AVISO] Opção inválida. ");
        pausar("Pressione ENTER para continuar... ");
    } while (opcao != 0);
}

/* 
  * Obs: As funções de menu abaixo utilizam o templete genérico definido acima.
  * Elas provavelmente precisarão ser reescritas quando o sistema estiver mais completo.
  * Sinta-se livre para modificá-las se precisar.
*/

// Menu do módulo de Pontos de Entrega
static void menu_pontos_entrega(void) {
    char *titulo = "Módulo 1 - Pontos de Entrega";
    char *matriz_opcoes[] = {
        "1 - Cadastrar ponto",
        "2 - Buscar ponto por código",
        "3 - Listar pontos em ordem crescente",
        "4 - Excluir ponto"
    };
    int num_opcoes = sizeof(matriz_opcoes) / sizeof(char*);
    exibir_menu_temp(titulo, matriz_opcoes, num_opcoes);
}

// Menu do módulo de Pedidos
static void menu_pedidos(void) {
    char *titulo = "Módulo 2 - Pedidos";
    char *matriz_opcoes[] = {
        "1 - Inserir pedido",
        "2 - Consultar próximo pedido",
        "3 - Processar despacho",
        "4 - Exibir pedidos pendentes"
    };
    int num_opcoes = sizeof(matriz_opcoes) / sizeof(char*);
    exibir_menu_temp(titulo, matriz_opcoes, num_opcoes);
}

// Menu do módulo de Histórico
static void menu_historico(void) {
    char *titulo = "Módulo 3 - Histórico";
    char *matriz_opcoes[] = {
        "1 - Consultar histórico completo",
        "2 - Buscar pedido por código de rastreio"
    };
    int num_opcoes = sizeof(matriz_opcoes) / sizeof(char*);
    exibir_menu_temp(titulo, matriz_opcoes, num_opcoes);
}

// Menu do módulo de Relatórios, Carga de Dados e Ordenação.
static void menu_relatorios(void) {
    char *titulo = "Módulo 4 - Relatórios";
    char *matriz_opcoes[] = {
        "1 - Relatório ordenado",
        "2 - Comparar algoritmos de ordenação",
        "3 - Carga inicial automatizada"
    };
    int num_opcoes = sizeof(matriz_opcoes) / sizeof(char*);
    exibir_menu_temp(titulo, matriz_opcoes, num_opcoes);
}

void iniciar_menu(void) {
    int opcao;
    FuncaoMenu menus[] = {
        menu_pontos_entrega,
        menu_pedidos,
        menu_historico,
        menu_relatorios
    };

    do {
        exibir_cabecalho("Menu Principal");
        printf("1 - Pontos de Entrega\n");
        printf("2 - Pedidos\n");
        printf("3 - Histórico\n");
        printf("4 - Relatórios\n");
        printf("0 - Sair\n");
        printf("------------------------------------------\n");

        exibir_prompt();
        opcao = ler_inteiro();
        if (opcao == 0) return;
        if (opcao > 0 && opcao <= 4) {
            menus[opcao - 1]();
            continue;
        }

        fprintf(stderr, "[AVISO] Opção inválida. ");
        pausar("Pressione ENTER para continuar... ");
    } while (opcao != 0);
}
