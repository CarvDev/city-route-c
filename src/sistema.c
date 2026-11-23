#include "sistema.h"
#include "bst.h"
#include "heap.h"
#include "historico.h"
#include "utils.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Auxiliares para gerar a carga inicial aleatória */

#define COD_RASTREIO_BASE 1000
#define LATITUDE_MIN (-33.75)
#define LATITUDE_MAX (5.27)
#define LONGITUDE_MIN (-73.99)
#define LONGITUDE_MAX (-34.79)
#define PESO_MIN (0.1)
#define PESO_MAX (50.0)
#define VALOR_MIN (10.0)
#define VALOR_MAX (5000.0)

static const char *const NOMES_BAIRROS[] = {
    "Centro", "Jardim América", "Vila Nova", "Boa Vista",
    "Santa Luzia", "São José", "Industrial", "Bela Vista",
    "Parque das Flores", "Alto da Serra"
};

/*
 * Semeia o gerador pseudoaleatório com o horário atual e um contador de
 * chamadas, evitando sequências idênticas em execuções/cargas seguidas.
 */
static void semear_aleatorio(void) {
    static unsigned long chamadas;
    unsigned long semente = (unsigned long)time(NULL) + chamadas++;
    srand((unsigned int)(semente ^ (semente >> 16)));
}

/* Gera de 0 a limite - 1 */
static size_t sorteio_size(size_t limite) {
    if (limite == 0) return 0;
    return (size_t)rand() % limite;
}

static double sorteio_double(double minimo, double maximo) {
    double escala = (double)rand() / (double)RAND_MAX;
    return minimo + (maximo - minimo) * escala;
}

/*
 * Prioridade ponderada: 10% Expressa (1), 30% VIP (2) e 60% Convencional (3).
 */
static int sortear_prioridade(void) {
    size_t chance = sorteio_size(100);
    if (chance < 10) return 1;
    if (chance < 40) return 2;
    return 3;
}

/* Embaralhamento de Fisher-Yates (in-place). */
static void embaralhar(int *vetor, size_t tamanho) {
    for (size_t i = tamanho; i > 1; i--) {
        size_t j = sorteio_size(i);
        int tmp = vetor[i - 1];
        vetor[i - 1] = vetor[j];
        vetor[j] = tmp;
    }
}

/* Funções públicas */

int sistema_iniciar(Sistema *s) {
    if (s == NULL) return 0;

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = historico_inicializar();
    if (s->historico == NULL) return 0;

    return 1;
}

void sistema_encerrar(Sistema *s) {
    if (s == NULL) return;

    bst_liberar(s->pontos);
    free(s->fila.dados);
    historico_liberar(s->historico);

    s->pontos = NULL;
    s->fila = (HeapPedidos){0};
    s->historico = NULL;
}

int sistema_despachar(Sistema *s, Pedido *saida) {
    if (s == NULL) return 0;

    const Pedido *proximo = heap_proximo(&s->fila);
    if (proximo == NULL) return 0;

    // Se o registro falhar, o pedido continua na fila.
    if (!historico_registrar(s->historico, *proximo)) return 0;

    return heap_extrair(&s->fila, saida);
}

int sistema_excluir_ponto(Sistema *s, int id) {
    if (s == NULL) return 0;

    for (size_t i = 0; i < s->fila.tamanho; i++) {
        if (s->fila.dados[i].id_destino == id) return 0;
    }

    int ok = 0;
    s->pontos = bst_remover(s->pontos, id, &ok);
    return ok;
}

int sistema_inserir_pedido(Sistema *s, Pedido pedido) {
    if (s == NULL || pedido.prioridade < 1 || pedido.prioridade > 3 ||
        !isfinite(pedido.peso) || pedido.peso <= 0 ||
        !isfinite(pedido.valor) || pedido.valor < 0 ||
        bst_buscar(s->pontos, pedido.id_destino) == NULL ||
        historico_buscar(s->historico, pedido.cod_rastreio) != NULL) {
        return 0;
    }

    for (size_t i = 0; i < s->fila.tamanho; i++) {
        if (s->fila.dados[i].cod_rastreio == pedido.cod_rastreio) return 0;
    }

    return heap_inserir(&s->fila, pedido);
}

int sistema_carga_teste(Sistema *s, size_t qtd_pontos, size_t qtd_pedidos) {
    if (s == NULL || qtd_pontos == 0 || qtd_pedidos == 0) return 0;
    if (qtd_pontos > (size_t)INT_MAX) return 0;
    if (mul_estoura_size(qtd_pedidos, 2)) return 0;

    const size_t total_cods = qtd_pedidos * 2;
    if (total_cods > (size_t)INT_MAX - COD_RASTREIO_BASE) return 0;
    if (mul_estoura_size(qtd_pontos, sizeof(int)) ||
        mul_estoura_size(total_cods, sizeof(int))) {
        return 0;
    }

    int resultado = 0;
    unsigned long ordem_chegada = 0;
    int *ids_pontos = NULL;
    int *cods_rastreio = NULL;

    // Reset seguro: descarta o estado atual antes de repovoar as estruturas.
    sistema_encerrar(s);
    if (!sistema_iniciar(s)) return 0;

    ids_pontos = malloc(qtd_pontos * sizeof *ids_pontos);
    cods_rastreio = malloc(total_cods * sizeof *cods_rastreio);
    if (ids_pontos == NULL || cods_rastreio == NULL) goto falha;

    semear_aleatorio();

    // IDs dos pontos embaralhados para evitar uma BST degenerada.
    for (size_t i = 0; i < qtd_pontos; i++) ids_pontos[i] = (int)(i + 1);
    embaralhar(ids_pontos, qtd_pontos);

    for (size_t i = 0; i < qtd_pontos; i++) {
        PontoEntrega ponto = {0};
        ponto.id_ponto = ids_pontos[i];

        const char *bairro = NOMES_BAIRROS[sorteio_size(NUM_ITENS(NOMES_BAIRROS))];
        snprintf(ponto.nome_local, sizeof ponto.nome_local, "%s - Setor %zu",
            bairro, 1 + sorteio_size(99));

        ponto.latitude = sorteio_double(LATITUDE_MIN, LATITUDE_MAX);
        ponto.longitude = sorteio_double(LONGITUDE_MIN, LONGITUDE_MAX);

        int ok = 0;
        s->pontos = bst_inserir(s->pontos, ponto, &ok);
        if (!ok) goto falha;
    }

    // Códigos de rastreio únicos e embaralhados (caso médio dos RF11/RF12).
    for (size_t i = 0; i < total_cods; i++) {
        cods_rastreio[i] = COD_RASTREIO_BASE + (int)i;
    }
    embaralhar(cods_rastreio, total_cods);

    for (size_t i = 0; i < total_cods; i++) {
        Pedido pedido = {0};
        pedido.cod_rastreio = cods_rastreio[i];
        pedido.prioridade = sortear_prioridade();
        pedido.ordem_chegada = ordem_chegada++;
        pedido.id_destino = ids_pontos[sorteio_size(qtd_pontos)];
        pedido.peso = (float)sorteio_double(PESO_MIN, PESO_MAX);
        pedido.valor = (float)sorteio_double(VALOR_MIN, VALOR_MAX);

        if (!sistema_inserir_pedido(s, pedido)) goto falha;

        // Uma a cada duas inserções é despachada, respeitando prioridade/FIFO.
        if (i % 2 == 1 && !sistema_despachar(s, NULL)) goto falha;
    }

    resultado = 1;

falha:
    free(ids_pontos);
    free(cods_rastreio);
    return resultado;
}
