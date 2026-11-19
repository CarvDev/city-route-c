#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Função auxiliar interna (encapsulada) para encontrar o nó de menor chave
 * em uma subárvore. Em uma BST, o menor elemento está sempre no nó mais à
 * esquerda da subárvore. É utilizado para determinar o sucessor em-ordem
 * durante a remoção de nós com dois filhos.
 */
static NoBST *encontrar_menor(NoBST *no) {
    /* Caso base: se não há filho à esquerda, este nó já possui a menor chave */
    if (no == NULL || no->esq == NULL) {
        return no;
    }
    /* Passo recursivo: continua descendo pela esquerda enquanto houver nós */
    return encontrar_menor(no->esq);
}

/*
 * Função auxiliar interna para alocar e inicializar um novo nó da árvore.
 * Isola a responsabilidade de alocação de memória e garante a inicialização
 * nula dos ponteiros dos filhos para manter a integridade da árvore.
 */
static NoBST *criar_no(PontoEntrega ponto) {
    /* Aloca memória dinamicamente no heap para o novo nó */
    NoBST *novo = (NoBST *)malloc(sizeof(NoBST));
    if (novo == NULL) {
        return NULL;
    }

    /* Copia os dados do ponto de entrega e inicializa as subárvores como folhas */
    novo->ponto = ponto;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/*
 * Inserção recursiva na BST baseada no id_ponto.
 *
 * Caso base 1 (árvore ou subárvore vazia): aloca o nó e o conecta aqui.
 * Caso recursivo: compara id_ponto para decidir se desce para subárvore
 * esquerda (chaves menores) ou direita (chaves maiores).
 * Tratamento de duplicatas: se a chave já existir, a estrutura não é alterada
 * e a operação sinaliza falha (*ok = 0), preservando a unicidade da chave.
 */
NoBST *bst_inserir(NoBST *raiz, PontoEntrega ponto, int *ok) {
    /* Caso base: alcançou posição vazia na árvore onde o novo nó deve ser inserido */
    if (raiz == NULL) {
        NoBST *novo = criar_no(ponto);
        if (novo == NULL) {
            /* Falha na alocação de memória pelo sistema operacional */
            if (ok != NULL) {
                *ok = 0;
            }
            return NULL;
        }
        /* Inserção bem-sucedida */
        if (ok != NULL) {
            *ok = 1;
        }
        return novo;
    }

    /* Casos recursivos guiados pela propriedade de busca da BST */
    if (ponto.id_ponto < raiz->ponto.id_ponto) {
        /* Chave menor: navega recursivamente para a subárvore esquerda e reconecta */
        raiz->esq = bst_inserir(raiz->esq, ponto, ok);
    } else if (ponto.id_ponto > raiz->ponto.id_ponto) {
        /* Chave maior: navega recursivamente para a subárvore direita e reconecta */
        raiz->dir = bst_inserir(raiz->dir, ponto, ok);
    } else {
        /* Chave duplicada encontrada: impede inserção redundante e sinaliza falha */
        if (ok != NULL) {
            *ok = 0;
        }
    }

    /* Retorna o ponteiro para a raiz atualizada com os links preservados */
    return raiz;
}

/*
 * Busca recursiva por id_ponto.
 *
 * O algoritmo explora a propriedade de ordenação da BST: a cada comparação,
 * descarta metade da árvore restante (em média), garantindo complexidade
 * proporcional à altura da árvore.
 *
 * Retorna ponteiro constante para o nó encontrado, ou NULL se a chave não existir.
 */
const NoBST *bst_buscar(const NoBST *raiz, int id_ponto) {
    /* Caso base 1: árvore vazia ou chave inexistente após percorrer o caminho */
    if (raiz == NULL) {
        return NULL;
    }

    /* Caso base 2: chave correspondente encontrada no nó atual */
    if (id_ponto == raiz->ponto.id_ponto) {
        return raiz;
    }

    /* Passo recursivo: direciona a busca com base na ordenação da chave */
    if (id_ponto < raiz->ponto.id_ponto) {
        return bst_buscar(raiz->esq, id_ponto);
    }

    return bst_buscar(raiz->dir, id_ponto);
}

/*
 * Listagem dos pontos em ordem crescente de id_ponto (percurso em-ordem: esq -> raiz -> dir).
 *
 * O percurso em-ordem em uma BST visita os nós em sequência estritamente
 * ordenada por sua chave de busca. O caso base simplesmente retorna sem
 * emitir mensagens para não poluir a saída a cada nó folha visitado.
 */
void bst_listar_em_ordem(const NoBST *raiz) {
    /* Caso base: nó nulo encerra o ramo sem imprimir mensagens espúrias */
    if (raiz == NULL) {
        return;
    }

    /* 1. Visita recursivamente todos os elementos menores (subárvore esquerda) */
    bst_listar_em_ordem(raiz->esq);

    /* 2. Processa o elemento do nó corrente */
    printf("ID: %d | Nome: %s | Latitude: %.6f | Longitude: %.6f\n",
           raiz->ponto.id_ponto,
           raiz->ponto.nome_local,
           raiz->ponto.latitude,
           raiz->ponto.longitude);

    /* 3. Visita recursivamente todos os elementos maiores (subárvore direita) */
    bst_listar_em_ordem(raiz->dir);
}

/*
 * Remoção recursiva na BST.
 *
 * A remoção deve preservar as propriedades da BST e lida com três cenários:
 * 1. Nó folha (0 filhos): basta desalocar e religar o ponteiro pai para NULL.
 * 2. Nó com 1 filho: substitui o nó atual diretamente pelo seu único filho,
 *    religando a subárvore existente ao pai.
 * 3. Nó com 2 filhos: para manter a ordenação da BST, localiza o sucessor
 *    em-ordem (menor nó da subárvore direita), copia seus dados para o nó atual
 *    e depois remove recursivamente o nó original do sucessor na subárvore direita.
 *
 * O uso de uma flag auxiliar na chamada recursiva garante que *ok permaneça com
 * valor 1 após o sucesso da substituição.
 */
NoBST *bst_remover(NoBST *raiz, int id_ponto, int *ok) {
    /* Caso base de parada: nó nulo indica que a chave não existe na árvore */
    if (raiz == NULL) {
        if (ok != NULL) {
            *ok = 0;
        }
        return NULL;
    }

    /* Etapa de busca recursiva do nó a ser removido */
    if (id_ponto < raiz->ponto.id_ponto) {
        raiz->esq = bst_remover(raiz->esq, id_ponto, ok);
    } else if (id_ponto > raiz->ponto.id_ponto) {
        raiz->dir = bst_remover(raiz->dir, id_ponto, ok);
    } else {
        /* Chave localizada: tratar os 3 casos de remoção */

        /* Caso 1 (Folha) e Caso 2 (Apenas filho direito):
         * Se esq é NULL, salva o filho direito (que pode ser NULL se for folha),
         * libera a memória do nó atual e retorna o filho para reconexão no pai.
         */
        if (raiz->esq == NULL) {
            NoBST *filho = raiz->dir;
            free(raiz);
            if (ok != NULL) {
                *ok = 1;
            }
            return filho;
        }

        /* Caso 2 (Apenas filho esquerdo):
         * Se dir é NULL, salva o filho esquerdo, libera o nó e retorna o filho.
         */
        if (raiz->dir == NULL) {
            NoBST *filho = raiz->esq;
            free(raiz);
            if (ok != NULL) {
                *ok = 1;
            }
            return filho;
        }

        /* Caso 3 (Dois filhos):
         * Não podemos simplesmente remover o nó pois romperíamos a árvore em duas partes.
         * Estratégia:
         * 1. Encontra o sucessor em-ordem (menor nó da subárvore direita).
         * 2. Copia os dados do sucessor para o nó corrente (preservando os ponteiros).
         * 3. Remove recursivamente o nó original do sucessor na subárvore direita.
         * Usa uma flag local (ok_recursivo) para isolar e assegurar que *ok mantenha 1.
         */
        {
            NoBST *sucessor = encontrar_menor(raiz->dir);
            int ok_recursivo = 0;
            raiz->ponto = sucessor->ponto;
            raiz->dir = bst_remover(raiz->dir, sucessor->ponto.id_ponto, &ok_recursivo);
            if (ok != NULL) {
                *ok = 1;
            }
        }
    }

    return raiz;
}

/*
 * Liberação de memória de todos os nós da BST em percurso pós-ordem.
 *
 * O percurso pós-ordem (esq -> dir -> raiz) é mandatório para desalocação de memória:
 * os nós filhos devem ser completamente liberados antes do nó pai, evitando
 * acessos a ponteiros já desalocados (use-after-free) e vazamentos de memória.
 */
void bst_liberar(NoBST *raiz) {
    /* Caso base: nó nulo não requer liberação */
    if (raiz == NULL) {
        return;
    }

    /* Desaloca recursivamente ambas as subárvores antes da raiz */
    bst_liberar(raiz->esq);
    bst_liberar(raiz->dir);

    /* Libera o próprio nó após garantir que seus filhos já foram liberados */
    free(raiz);
}
