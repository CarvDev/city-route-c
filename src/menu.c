#include <stddef.h>
#include <stdio.h>

#include "entrada.h"
#include "menu.h"
#include "sistema.h"
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

void exibir_ajuda(void) {
    puts(
        "CityRoute C - Sistema de Logística Urbana e Gerenciamento de Pedidos\n"
        "\n"
        "Uso:\n"
        "  ./cityroute [OPÇÕES]\n"
        "\n"
        "Opções:\n"
        "  -h, --help    Exibe este manual e encerra sem abrir o menu.\n"
        "  (nenhuma)     Inicia o menu interativo.\n"
        "\n"
        "Menu principal:\n"
        "  1 - Pontos de Entrega   Cadastrar, buscar, listar e excluir pontos (BST).\n"
        "  2 - Pedidos             Inserir, consultar, despachar e listar pendentes (heap).\n"
        "  3 - Histórico           Listar entregas e buscar por rastreio (lista).\n"
        "  4 - Relatórios          Relatório ordenado, comparação e carga de dados.\n"
        "  5 - Ajuda               Exibe este manual.\n"
        "  0 - Sair                Encerra o programa e libera a memória.\n"
        "\n"
        "Navegação:\n"
        "  Digite o número da opção e pressione ENTER; 0 volta ou sai.\n"
        "  Após cada operação, pressione ENTER na pausa exibida.\n"
        "\n"
        "Dados digitados:\n"
        "  Inteiros: um valor por linha (ID, rastreio, prioridade 1/2/3).\n"
        "  Nome do local: texto não vazio de até 99 caracteres.\n"
        "  Decimais: use ponto como separador (ex.: -14.8167); peso > 0 e valor >= 0.\n"
        "  Prioridade: 1 Expressa, 2 VIP, 3 Convencional; desempate por ordem de chegada.\n"
        "\n"
        "Exemplos:\n"
        "  ./cityroute           Inicia o menu interativo.\n"
        "  ./cityroute --help    Exibe este manual.\n"
        "  ./cityroute -h        Atalho para --help."
    );
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

// Wrapper para passar exibir_ajuda como item de menu
static void menu_ajuda(struct Sistema *s) {
    (void)s; // para evitar "warning: unused parameter" 
    puts(LINHA_PADRAO);
    exibir_ajuda();
    puts(LINHA_PADRAO);
    pausar(PAUSA_PADRAO);
}

static const ItemMenu ITENS_PRINCIPAL[] = {
    { "Pontos de Entrega", menu_pontos_entrega },
    { "Pedidos",           menu_pedidos },
    { "Histórico",         menu_historico },
    { "Relatórios",        menu_relatorios },
    { "Ajuda",             menu_ajuda }
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
        int opcao;
        if (!ler_int(&opcao)) {
            fprintf(stderr, "[ERRO] Falha na leitura da opção\n");
            pausar(PAUSA_PADRAO);
            continue;
        }

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
        pausar(PAUSA_PADRAO);
    }
}

void iniciar_menu(struct Sistema *s) {
    executar_menu("Menu Principal", ITENS_PRINCIPAL,
        NUM_ITENS(ITENS_PRINCIPAL), s);
}
