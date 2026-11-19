#include "bst.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Função utilitária para inicializar uma struct PontoEntrega nos testes */
static PontoEntrega criar_ponto(int id, const char *nome, double lat, double lon) {
    PontoEntrega p;
    p.id_ponto = id;
    strncpy(p.nome_local, nome, sizeof(p.nome_local) - 1);
    p.nome_local[sizeof(p.nome_local) - 1] = '\0';
    p.latitude = lat;
    p.longitude = lon;
    return p;
}

/* 1. Inserção em ordem arbitrária e verificação de integridade */
static void test_insercao_e_integridade(void) {
    NoBST *raiz = NULL;
    int ok = 0;

    int chaves[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 65, 75, 85};
    size_t total = sizeof(chaves) / sizeof(chaves[0]);

    for (size_t i = 0; i < total; i++) {
        PontoEntrega p = criar_ponto(chaves[i], "Ponto Teste", -23.55, -46.63);
        raiz = bst_inserir(raiz, p, &ok);
        assert(ok == 1);
        assert(raiz != NULL);
    }

    /* Verifica se todos os nós inseridos estão presentes e com dados íntegros */
    for (size_t i = 0; i < total; i++) {
        const NoBST *encontrado = bst_buscar(raiz, chaves[i]);
        assert(encontrado != NULL);
        assert(encontrado->ponto.id_ponto == chaves[i]);
        assert(strcmp(encontrado->ponto.nome_local, "Ponto Teste") == 0);
        assert(encontrado->ponto.latitude == -23.55);
        assert(encontrado->ponto.longitude == -46.63);
    }

    bst_liberar(raiz);
    printf("[OK] Teste 1: Inserção arbitrária e integridade\n");
}

/* 2. Tentativa de inserção de chave duplicada */
static void test_insercao_duplicada(void) {
    NoBST *raiz = NULL;
    int ok = 0;

    PontoEntrega p1 = criar_ponto(100, "Centro", -23.50, -46.60);
    raiz = bst_inserir(raiz, p1, &ok);
    assert(ok == 1);

    /* Tentativa de inserir o mesmo id_ponto com outros dados */
    PontoEntrega p1_duplicado = criar_ponto(100, "Novo Centro Alterado", -23.99, -46.99);
    raiz = bst_inserir(raiz, p1_duplicado, &ok);
    assert(ok == 0);

    /* Confirma que os dados originais foram estritamente preservados */
    const NoBST *busca = bst_buscar(raiz, 100);
    assert(busca != NULL);
    assert(strcmp(busca->ponto.nome_local, "Centro") == 0);
    assert(busca->ponto.latitude == -23.50);
    assert(busca->ponto.longitude == -46.60);

    bst_liberar(raiz);
    printf("[OK] Teste 2: Inserção de chave duplicada\n");
}

/* 3. Busca em árvore vazia, busca por ponto existente e inexistente */
static void test_busca(void) {
    NoBST *raiz = NULL;

    /* Busca em árvore vazia */
    assert(bst_buscar(raiz, 10) == NULL);

    int ok = 0;
    raiz = bst_inserir(raiz, criar_ponto(50, "P50", 0.0, 0.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(25, "P25", 0.0, 0.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(75, "P75", 0.0, 0.0), &ok);

    /* Busca por nós existentes */
    assert(bst_buscar(raiz, 50) != NULL);
    assert(bst_buscar(raiz, 25) != NULL);
    assert(bst_buscar(raiz, 75) != NULL);

    /* Busca por nós inexistentes (menor, intermediário e maior) */
    assert(bst_buscar(raiz, 10) == NULL);
    assert(bst_buscar(raiz, 40) == NULL);
    assert(bst_buscar(raiz, 60) == NULL);
    assert(bst_buscar(raiz, 100) == NULL);

    bst_liberar(raiz);
    printf("[OK] Teste 3: Busca em cenários variados\n");
}

/* 4. Listagem em-ordem */
static void test_listagem_em_ordem(void) {
    /* Chamada em árvore vazia não deve imprimir nada nem falhar */
    printf("--- Início teste listagem árvore vazia (não deve imprimir nós) ---\n");
    bst_listar_em_ordem(NULL);
    printf("--- Fim teste listagem árvore vazia ---\n");

    NoBST *raiz = NULL;
    int ok = 0;
    raiz = bst_inserir(raiz, criar_ponto(30, "Ponto B", 1.0, 2.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(10, "Ponto A", 3.0, 4.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(20, "Ponto AB", 5.0, 6.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(50, "Ponto D", 7.0, 8.0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(40, "Ponto C", 9.0, 10.0), &ok);

    printf("--- Listagem em-ordem esperada (10, 20, 30, 40, 50) ---\n");
    bst_listar_em_ordem(raiz);
    printf("--- Fim listagem em-ordem ---\n");

    bst_liberar(raiz);
    printf("[OK] Teste 4: Listagem em-ordem concluída\n");
}

/* 5. Cenários completos de remoção */
static void test_remocao(void) {
    NoBST *raiz = NULL;
    int ok = 0;

    /* Remoção em árvore vazia */
    raiz = bst_remover(raiz, 10, &ok);
    assert(raiz == NULL);
    assert(ok == 0);

    /* Monta árvore de teste:
     *         50
     *       /    \
     *     30      70
     *    /  \    /  \
     *   20  40  60  80
     *  /         \
     * 10         65
     */
    int chaves[] = {50, 30, 70, 20, 40, 60, 80, 10, 65};
    for (size_t i = 0; i < sizeof(chaves)/sizeof(chaves[0]); i++) {
        raiz = bst_inserir(raiz, criar_ponto(chaves[i], "Ponto", 0.0, 0.0), &ok);
    }

    /* Remoção de chave inexistente */
    raiz = bst_remover(raiz, 999, &ok);
    assert(ok == 0);
    assert(bst_buscar(raiz, 50) != NULL);

    /* 5.1 Nó folha (0 filhos): nó 10 e nó 40 */
    raiz = bst_remover(raiz, 10, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 10) == NULL);

    raiz = bst_remover(raiz, 40, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 40) == NULL);

    /* 5.2 Nó com apenas 1 filho esquerdo:
     * O nó 20 agora tem 0 filhos pois o 10 era seu filho esquerdo.
     * Vamos inserir o 15 para 20 ter apenas filho esquerdo.
     */
    raiz = bst_inserir(raiz, criar_ponto(15, "P15", 0.0, 0.0), &ok);
    assert(ok == 1);
    /* Remove 20 (tem apenas filho esquerdo 15) */
    raiz = bst_remover(raiz, 20, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 20) == NULL);
    assert(bst_buscar(raiz, 15) != NULL);

    /* 5.3 Nó com apenas 1 filho direito:
     * O nó 60 possui filho direito 65 e nenhum filho esquerdo.
     */
    raiz = bst_remover(raiz, 60, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 60) == NULL);
    assert(bst_buscar(raiz, 65) != NULL);

    /* 5.4 Nó com 2 filhos:
     * Nó 70 agora tem filhos: esquerdo 65 e direito 80.
     */
    raiz = bst_remover(raiz, 70, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 70) == NULL);
    assert(bst_buscar(raiz, 65) != NULL);
    assert(bst_buscar(raiz, 80) != NULL);

    /* 5.5 Remoção da própria raiz com 2 filhos (raiz atual é 50) */
    raiz = bst_remover(raiz, 50, &ok);
    assert(ok == 1);
    assert(bst_buscar(raiz, 50) == NULL);
    assert(raiz != NULL);
    /* Nós remanescentes devem continuar acessíveis: 15, 30, 65, 80 */
    assert(bst_buscar(raiz, 15) != NULL);
    assert(bst_buscar(raiz, 30) != NULL);
    assert(bst_buscar(raiz, 65) != NULL);
    assert(bst_buscar(raiz, 80) != NULL);

    bst_liberar(raiz);
    raiz = NULL;

    /* 5.6 Remoção da raiz em casos de 0 e 1 filho */
    /* Caso raiz folha (1 nó no total) */
    raiz = bst_inserir(raiz, criar_ponto(100, "RaizUnica", 0, 0), &ok);
    raiz = bst_remover(raiz, 100, &ok);
    assert(ok == 1);
    assert(raiz == NULL);

    /* Caso raiz com 1 filho esquerdo */
    raiz = bst_inserir(raiz, criar_ponto(100, "Raiz", 0, 0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(50, "FilhoEsq", 0, 0), &ok);
    raiz = bst_remover(raiz, 100, &ok);
    assert(ok == 1);
    assert(raiz != NULL && raiz->ponto.id_ponto == 50);
    bst_liberar(raiz);
    raiz = NULL;

    /* Caso raiz com 1 filho direito */
    raiz = bst_inserir(raiz, criar_ponto(100, "Raiz", 0, 0), &ok);
    raiz = bst_inserir(raiz, criar_ponto(150, "FilhoDir", 0, 0), &ok);
    raiz = bst_remover(raiz, 100, &ok);
    assert(ok == 1);
    assert(raiz != NULL && raiz->ponto.id_ponto == 150);
    bst_liberar(raiz);

    printf("[OK] Teste 5: Todos os cenários de remoção validados\n");
}

/* 6. Robustez com ponteiro ok = NULL */
static void test_robustez_ponteiro_nulo(void) {
    NoBST *raiz = NULL;

    /* Inserção com ok = NULL */
    raiz = bst_inserir(raiz, criar_ponto(20, "P20", 0, 0), NULL);
    assert(raiz != NULL);
    raiz = bst_inserir(raiz, criar_ponto(10, "P10", 0, 0), NULL);
    raiz = bst_inserir(raiz, criar_ponto(30, "P30", 0, 0), NULL);

    /* Inserção duplicada com ok = NULL (não deve crashar) */
    raiz = bst_inserir(raiz, criar_ponto(20, "P20_dup", 0, 0), NULL);

    /* Remoção em árvore vazia com ok = NULL */
    assert(bst_remover(NULL, 10, NULL) == NULL);

    /* Remoção de elemento existente com ok = NULL */
    raiz = bst_remover(raiz, 10, NULL);
    assert(bst_buscar(raiz, 10) == NULL);

    /* Remoção de elemento inexistente com ok = NULL */
    raiz = bst_remover(raiz, 999, NULL);

    bst_liberar(raiz);
    printf("[OK] Teste 6: Robustez com ok == NULL\n");
}

/* 7. Liberação de memória */
static void test_liberacao_memoria(void) {
    /* Chamada com NULL */
    bst_liberar(NULL);

    NoBST *raiz = NULL;
    int ok = 0;
    for (int i = 1; i <= 50; i++) {
        raiz = bst_inserir(raiz, criar_ponto(i, "Ponto", (double)i, (double)i), &ok);
    }
    bst_liberar(raiz);
    printf("[OK] Teste 7: Liberação de memória concluída\n");
}

int main(void) {
    printf("========================================\n");
    printf("Iniciando testes unitários do Módulo BST\n");
    printf("========================================\n");

    test_insercao_e_integridade();
    test_insercao_duplicada();
    test_busca();
    test_listagem_em_ordem();
    test_remocao();
    test_robustez_ponteiro_nulo();
    test_liberacao_memoria();

    printf("========================================\n");
    printf("Todos os testes passaram com sucesso!\n");
    printf("========================================\n");

    return 0;
}
