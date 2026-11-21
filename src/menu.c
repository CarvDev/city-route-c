#include <stddef.h>
#include <stdio.h>

#include "entrada.h"
#include "menu.h"
#include "utils.h"
#include "ui_ponto.h"
#include "ui_pedido.h"
#include "ui_historico.h"
#include "ui_relatorio.h"

static const char *PROMPT = "> ";

// Exibe o cabeçalho do sistema seguido do título da tela atual.
static void exibir_cabecalho(const char *titulo) {
    printf("\n");
    printf("==========================================\n");
    printf("              CITYROUTE C\n");
    printf("   Logística Urbana e Gestão de Pedidos\n");
    printf("==========================================\n");
    printf("%s\n", titulo);
    puts(LINHA_PADRAO);
}

// Imprime o prompt definido globalmente
void exibir_prompt(void) {
    printf("%s", PROMPT);
    fflush(stdout);
}

// Informa que a funcionalidade escolhida ainda será implementada.
static void exibir_placeholder(void) {
    printf("[AVISO] Esta funcionalidade do módulo será implementada em breve. ");
    pausar("Pressione ENTER para continuar... ");
}

static const ItemMenu ITENS_PRINCIPAL[] = {
    { "Pontos de Entrega", menu_pontos_entrega },
    { "Pedidos",           menu_pedidos },
    { "Historico",         menu_historico },
    { "Relatorios",        menu_relatorios }
};

void executar_menu(const char *titulo, const ItemMenu *itens, 
    size_t n, struct Sistema *s) 
{
    if (titulo == NULL || (itens == NULL && n > 0)) {
        return;
    }
    const char *rotulo_saida = (itens == ITENS_PRINCIPAL)? "Sair" : "Voltar";

    for (;;) {
        exibir_cabecalho(titulo);
        for (size_t i = 0; i < n; i++) {
            printf("%zu - %s\n", i + 1, itens[i].rotulo);
        }
        printf("0 - %s\n", rotulo_saida);
        puts(LINHA_PADRAO);

        exibir_prompt();
        int opcao = ler_inteiro();

        if (opcao == 0) {
            return;
        }

        if (opcao > 0 && (size_t)opcao <= n) {
            const ItemMenu *item = &itens[opcao - 1];
            if (item->acao != NULL) {
                item->acao(s);
            } else {
                exibir_placeholder();
            }
            continue;
        }

        fprintf(stderr, "[AVISO] Opção inválida. ");
        pausar("Pressione ENTER para continuar... ");
    }
}

void iniciar_menu(struct Sistema *s) {
    executar_menu("Menu Principal", ITENS_PRINCIPAL,
        NUM_ITENS(ITENS_PRINCIPAL), s);
}
